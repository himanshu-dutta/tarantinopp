#include "tarantinopp/network/tcp.h"

namespace tarantinopp {
namespace network {

// TCP Client
TCPSocketClient::TCPSocketClient(int32_t sockFd, sockaddr_in addr,
                                 std::shared_ptr<Logger> logger)
    : m_socketFd(sockFd), m_addr(addr), m_logger(logger) {}

void TCPSocketClient::disconnect() { close(m_socketFd); }

ByteVector TCPSocketClient::read(size_t numBytes) {
  Byte buffer[MAX_BUFFER_SIZE];
  ByteVector bytes;

  size_t bytesRead =
      recv(m_socketFd, buffer, std::min(MAX_BUFFER_SIZE, numBytes), 0);
  bytes.insert(bytes.end(), buffer, buffer + bytesRead);

  return bytes;
}

bool TCPSocketClient::write(ByteVector bytes) {
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

std::string TCPSocketClient::getClientInfo() {
  std::string info;
  char addr[128];
  inet_ntop(AF_INET, &(m_addr.sin_addr), addr, 128);

  info += addr;
  info += ":";
  info += std::to_string(m_addr.sin_port);
  return info;
}

std::shared_ptr<Logger> TCPSocketClient::getLogger() { return m_logger; };

TCPSocketClient::~TCPSocketClient() { disconnect(); }

// TCP Server
TCPSocket::TCPSocket(SocketApplication app, const char* host, uint16_t port,
                     uint32_t numBacklogs, int32_t numThreads,
                     std::shared_ptr<Logger> logger)
    : m_application(app), m_workerThreadpool(numThreads), m_logger(logger) {
  m_numBacklogs = numBacklogs;
  m_host = host;
  m_port = port;

  m_ServerAddr.sin_family = AF_INET;
  m_ServerAddr.sin_port = htons(m_port);
  m_ServerAddr.sin_addr.s_addr = inet_addr(m_host);

  if ((m_listenerSocketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    throw std::runtime_error("unable to initiate a listener socket");

  const int32_t enable = 1;
  if ((setsockopt(m_listenerSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable,
                  sizeof(int))) < 0)
    throw std::runtime_error("unable to establish resuable address");
  if (bind(m_listenerSocketFd, (sockaddr*)&m_ServerAddr, sizeof(m_ServerAddr)) <
      0)
    throw std::runtime_error(
        "unable to associate address with the open socket");
}

TCPSocket::~TCPSocket() { shutdown(); }

void TCPSocket::run() {
  if ((listen(m_listenerSocketFd, m_numBacklogs)) < 0)
    throw std::runtime_error("unable to initiate listening on the open socket");

  while (true) {
    sockaddr_in clientAddr;
    uint32_t clientAddrSize = sizeof(clientAddr);
    int32_t clientSocketFd =
        accept(m_listenerSocketFd, (sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSocketFd < 0) {
      getLogger()->info("Unable to conncet to a client");
      continue;
    }

    std::shared_ptr<SocketClient> client(
        new TCPSocketClient(clientSocketFd, clientAddr, getLogger()));
    m_clients.push_back(client);
    m_workerThreadpool.queueJob(m_application, client);
  }
}

void TCPSocket::shutdown() {
  m_workerThreadpool.close();
  close(m_listenerSocketFd);
  for (auto client : m_clients) client->disconnect();
}

std::shared_ptr<Logger> TCPSocket::getLogger() {
  if (m_logger == nullptr) throw std::runtime_error("logger not initiated");
  return m_logger;
}

}  // namespace network
}  // namespace tarantinopp