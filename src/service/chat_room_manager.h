#ifndef CHAT_ROOM_MANAGER_H
#define CHAT_ROOM_MANAGER_H

#include <QObject>
#include <QHash>
#include <QList>

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
    void setCurRoom(u64 room_id);

public slots:
    void onMessagesFetched(const QList<tcc::model::Message>& msgs);

private:
    model::MessageModel* message_model_;
    model::MessageDelegate* message_delegate_;

    u64 cur_room_;
    u64 cur_user_id_;
};
}  // namespace tcc::service
#endif  // CHAT_ROOM_MANAGER_H
