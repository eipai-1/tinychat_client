#include "chat_room_manager.h"
#include "net/net_manager.h"

using MessageModel = tcc::model::MessageModel;
using MessageDelegate = tcc::model::MessageDelegate;
using NetManager = tcc::net::NetManager;

namespace tcc::service {
ChatRoomManager::ChatRoomManager(QObject* parent) : QObject(parent) {}

ChatRoomManager::ChatRoomManager(QObject* parent, u64 cur_user_id)
    : QObject(parent), cur_user_id_(cur_user_id) {
    connect(&NetManager::get(), &NetManager::messagesFetched, this,
            &ChatRoomManager::onMessagesFetched);

    message_model_ = new MessageModel(this, cur_user_id);
    message_delegate_ = new MessageDelegate(this);
}

void ChatRoomManager::setCurRoom(u64 room_id) {
    if (cur_room_ == room_id) {
        return;
    }

    cur_room_ = room_id;
    message_model_->setCurRoom(cur_room_);
}

void ChatRoomManager::onMessagesFetched(const QList<model::Message>& msgs) {
    if (msgs.empty()) {
        return;
    }

    u64 room_id = msgs.front().room_id;

    for (const auto& e : msgs) {
        qDebug() << "Message: " << e.content << ", sender_id: " << e.sender_id;
    }

    message_model_->addMessageByRoom(msgs);
}
}  // namespace tcc::service
