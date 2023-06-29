#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>
#include <stdexcept>
#include <thread>
#include <tuple>
#include <utility>

namespace tarantinopp {
namespace concurrency {
const uint32_t MAX_THREADS =
    std::thread::hardware_concurrency()
    << 7;  // a heuristic metric of 128 threads per CPU core.

template <typename Task, typename... Args>
class Threadpool {
 public:
  Threadpool(int32_t num_threads = -1) {
    m_shouldClose = false;
    m_shouldAcceptJob = true;

    m_NumThreads =
        num_threads <= 0
            ? (MAX_THREADS)
            : (std::min({static_cast<uint32_t>(num_threads), MAX_THREADS}));
    m_threads.resize(m_NumThreads);
    for (uint32_t idx = 0; idx < m_NumThreads; ++idx)
      m_threads[idx] = std::thread(&Threadpool::threadLoop, this);
  }

  ~Threadpool() { close(); }
  void queueJob(Task t, Args... args) {
    if (!m_shouldAcceptJob)
      throw std::runtime_error("can't add jobs after close is called");

    {
      std::lock_guard<std::mutex> lock(m_jobsMutex);
      m_jobs.push({std::function<void(Args...)>(t), args...});
    }
    m_jobsMutexCond.notify_one();
  }
  void close() {
    {
      std::unique_lock<std::mutex> lock(m_jobsMutex);
      m_shouldAcceptJob = false;
    }
    while (hasPendingJobs())
      ;
    {
      std::unique_lock<std::mutex> lock(m_jobsMutex);
      m_shouldClose = true;
    }

    m_jobsMutexCond.notify_all();
    for (std::thread& thread : m_threads)
      if (thread.joinable()) thread.join();
    m_threads.clear();
  }

 private:
  bool hasPendingJobs() {
    bool hasPending;
    {
      std::unique_lock<std::mutex> lock(m_jobsMutex);
      hasPending = !m_jobs.empty();
    }
    return hasPending;
  }

  void threadLoop() {
    auto execute = [](Task t, Args... args) { t(args...); };
    std::optional<Job> job;
    while (true) {
      {
        std::unique_lock<std::mutex> lock(m_jobsMutex);
        m_jobsMutexCond.wait(
            lock, [this]() { return !m_jobs.empty() || m_shouldClose; });

        if (m_shouldClose) return;

        job = std::move(m_jobs.front());
        m_jobs.pop();
      }
      if (job) {
        std::apply(execute, *job);
        job.reset();
      }
    }
  }

 private:
  using Job = std::tuple<Task, Args...>;
  uint32_t m_NumThreads;
  std::queue<Job> m_jobs;
  std::vector<std::thread> m_threads;
  mutable std::mutex m_jobsMutex;
  std::condition_variable m_jobsMutexCond;
  bool m_shouldClose;
  bool m_shouldAcceptJob;
};

}  // namespace concurrency
}  // namespace tarantinopp