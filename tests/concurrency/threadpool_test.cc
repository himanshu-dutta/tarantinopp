#include "tarantinopp/concurrency/threadpool.h"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>

using namespace tarantinopp::concurrency;

TEST(concurrency, threadpool_no_args) {
  Threadpool<std::function<void()>> tp;

  const auto task = []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  for (int idx = 0; idx < 10; ++idx) tp.queueJob(task);
}

TEST(concurrency, threadpool_args) {
  Threadpool<std::function<void(int)>, int> tp(100);

  const auto task = [](int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("Value of x: %d\n", x);
    fflush(stdout);
  };

  for (int idx = 0; idx < 10; ++idx) tp.queueJob(task, idx);
}

TEST(concurrency, singleThread) {
  const auto task = []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  };

  for (int idx = 0; idx < 10; ++idx) task();
}
