#pragma once

#include <memory>

#include "tarantinopp/core/log.h"
#include "tarantinopp/server/environ.h"
#include "tarantinopp/server/receive.h"
#include "tarantinopp/server/send.h"

namespace tarantinopp {

class Application {
 public:
  Application(std::string name, std::shared_ptr<Logger> logger = nullptr);
  void operator()(server::Environment env, server::ReceiveFn receive,
                  server::SendFn send);

  std::shared_ptr<Logger> getLogger();

 private:
  std::string m_name;
  std::shared_ptr<Logger> m_logger;
};

}  // namespace tarantinopp