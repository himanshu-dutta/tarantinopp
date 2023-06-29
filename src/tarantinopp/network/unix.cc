#include "tarantinopp/network/unix.h"

namespace tarantinopp {
namespace network {
// Unix Socket Client
UnixSocketClient::UnixSocketClient(int32_t socketFd, sockaddr_un addr,
                                   std::shared_ptr<Logger> logger)
    : m_socketFd(socketFd), m_addr(addr), m_logger(logger) {}

UnixSocketClient::~UnixSocketClient() { disconnect(); }

ByteVector UnixSocketClient::read(size_t numBytes) {
  ByteVector bytes;
  Byte buffer[MAX_BUFFER_SIZE];

  size_t bytesRead =
      recv(m_socketFd, (void *)buffer, std::min(MAX_BUFFER_SIZE, numBytes), 0);
  bytes.insert(bytes.end(), buffer, buffer + bytesRead);

  return bytes;
}

bool UnixSocketClient::write(ByteVector bytes) {
  size_t numBytes = bytes.size();
  size_t numRemainingBytes = numBytes;
  while (numRemainingBytes) {
    int32_t bytesWritten =
        send(m_socketFd, bytes.data() + (numBytes - numRemainingBytes),
             numRemainingBytes, 0);
    if (bytesWritten < 0) break;
    numRemainingBytes -= bytesWritten;
  }
  return (numRemainingBytes == 0);
}

std::string UnixSocketClient::getClientInfo() {
  return std::string(m_addr.sun_path);
}

std::shared_ptr<Logger> UnixSocketClient::getLogger() { return m_logger; }

void UnixSocketClient::disconnect() { close(m_socketFd); }

// Unix Socket Server
UnixSocket::UnixSocket(std::string socketFilePath, uint32_t numBacklogs,
                       int32_t numThreads, std::shared_ptr<Logger> logger)
    : m_workerThreadpool(numThreads), m_logger(logger) {
  m_socketFilePath =
      socketFilePath != "" ? socketFilePath : (std::string("./") + "socket");
  m_numBacklogs = numBacklogs;

  populateServerAddress();

  if ((m_listenerSocketFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    throw std::runtime_error("uable to allocate socket file descriptor");

  try {
    std::filesystem::remove(m_socketFilePath);
  } catch (const std::filesystem::filesystem_error &err) {
  }

  if (bind(m_listenerSocketFd, (sockaddr *)&m_serverAddr,
           sizeof(m_serverAddr)) < 0)
    throw std::runtime_error("unable to bind address to the socket");

  if (chmod(m_socketFilePath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) < 0)
    throw std::runtime_error(
        "unable to add read/write permission to socket file descriptor");
}

UnixSocket::~UnixSocket() { shutdown(); }

void UnixSocket::operator()(SocketApplication handler) {
  if (listen(m_listenerSocketFd, m_numBacklogs) < 0)
    throw std::runtime_error("unable to initiate listening on the socket");

  while (true) {
    sockaddr_un clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    int32_t clientSocketFd =
        accept(m_listenerSocketFd, (sockaddr *)&clientAddr, &clientAddrSize);
    if (clientSocketFd < 0) {
      getLogger()->info("Unable to connect to a client");
      continue;
    }

    std::shared_ptr<SocketClient> client(
        new UnixSocketClient(clientSocketFd, clientAddr, getLogger()));
    m_clients.push_back(client);
    m_workerThreadpool.queueJob(handler, client);
  }
}

void UnixSocket::shutdown() {
  close(m_listenerSocketFd);
  m_workerThreadpool.close();
  for (auto client : m_clients) client->disconnect();
}

std::shared_ptr<Logger> UnixSocket::getLogger() {
  if (m_logger == nullptr) throw std::runtime_error("logger not initiated");
  return m_logger;
}

void UnixSocket::populateServerAddress() {
  memset(&m_serverAddr, 0, sizeof(m_serverAddr));
  m_serverAddr.sun_family = AF_UNIX;
  if (m_socketFilePath.length() > (sizeof(m_serverAddr.sun_path) - 1))
    throw std::length_error("socket file path longer than expected");
  strncpy(m_serverAddr.sun_path, m_socketFilePath.c_str(),
          (sizeof(m_serverAddr.sun_path) - 1));

#ifdef __APPLE__
  m_serverAddr.sun_len = m_socketFilePath.length() + 1;
#endif
}

}  // namespace network
}  // namespace tarantinopp