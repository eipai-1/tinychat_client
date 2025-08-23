#include "chat_room_manager.h"
#include "net/net_manager.h"
#include "net/websocket_client.h"

using MessageModel = tcc::model::MessageModel;
using MessageDelegate = tcc::model::MessageDelegate;
using NetManager = tcc::net::NetManager;
using WebSocketClient = tcc::net::WebSocketClient;
using Message = tcc::model::Message;
using Room = tcc::model::Room;

namespace tcc::service {
ChatRoomManager::ChatRoomManager(QObject* parent) : QObject(parent) {}

ChatRoomManager::ChatRoomManager(QObject* parent, u64 cur_user_id)
    : QObject(parent), cur_user_id_(cur_user_id) {
    connect(&NetManager::get(), &NetManager::messagesFetched, this,
            &ChatRoomManager::onMessagesFetched);

    message_model_ = new MessageModel(this, cur_user_id);
    message_delegate_ = new MessageDelegate(this);
    connect(NetManager::get().websocketClient(), &WebSocketClient::chatMsgReceived, this,
            &ChatRoomManager::onChatMsgReceived);
    cur_room_type_ = Room::Type::Invalid;
}

void ChatRoomManager::setCurRoom(u64 room_id, Room::Type type) {
    if (cur_room_id_ == room_id) {
        return;
    }

    cur_room_id_ = room_id;
    cur_room_type_ = type;
    message_model_->setCurRoom(cur_room_id_);
}

void ChatRoomManager::onChatMsgReceived(const Message& msg) {
    qDebug() << "received msg:" << msg.content;
    message_model_->addMsg(msg);
}

void ChatRoomManager::onMessagesFetched(const QList<model::Message>& msgs) {
    if (msgs.empty()) {
        return;
    }

    u64 room_id = msgs.front().room_id;

    for (const auto& e : msgs) {
        qDebug() << "Message: " << e.content << ", sender_id: " << e.sender_id;
    }

    message_model_->addMsgsByRoom(msgs);
}
}  // namespace tcc::service
