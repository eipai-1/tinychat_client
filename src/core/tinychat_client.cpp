#include "tinychat_client.h"
#include "net/net_manager.h"

namespace tcc {
namespace core {

TinychatClient::TinychatClient() {
    tcc::net::NetManager::init();
}

void TinychatClient::run()
{
    controller_.run();
}

} // namespace core
} // namespace tcc
