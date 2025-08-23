#ifndef CHAT_ROOM_MANAGER_H
#define CHAT_ROOM_MANAGER_H

#include <QObject>
#include <QHash>
#include <QList>

#include "model/room.h"
#include "model/message.h"
#include "model/message_model.h"
#include "model/message_delegate.h"
#include "utils/types.h"

namespace tcc::service {
class ChatRoomManager : public QObject {
    Q_OBJECT
public:
    explicit ChatRoomManager(QObject* parent = nullptr);
    explicit ChatRoomManager(QObject* parent, u64 cur_user_id);
    model::MessageModel* messageModel() const { return message_model_; }
    model::MessageDelegate* messageDelegate() const { return message_delegate_; }
    void setCurRoom(u64 room_id, model::Room::Type type);
    u64 curRoomId() const { return cur_room_id_; }
    model::Room::Type curRoomType() const { return cur_room_type_; }

public slots:
    void onMessagesFetched(const QList<tcc::model::Message>& msgs);
    void onChatMsgReceived(const tcc::model::Message& msg);

private:
    model::MessageModel* message_model_;
    model::MessageDelegate* message_delegate_;

    u64 cur_room_id_ = 0;
    u64 cur_user_id_;
    model::Room::Type cur_room_type_;
};
}  // namespace tcc::service
#endif  // CHAT_ROOM_MANAGER_H
