#include "tinychat_client.h"
#include "net/net_manager.h"

#include "model/room.h"
#include "model/message.h"

namespace tcc {
namespace core {

TinychatClient::TinychatClient() {
    qRegisterMetaType<tcc::model::Room>();
    qRegisterMetaType<tcc::model::Message>();

    tcc::net::NetManager::init();
}

void TinychatClient::run() { controller_.run(); }

}  // namespace core
}  // namespace tcc
