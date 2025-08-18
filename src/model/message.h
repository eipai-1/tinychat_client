#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QVariant>

#include "utils/types.h"

namespace tcc::model {
struct Message {
    u64 id;
    u64 room_id;
    u64 sender_id;
    int content_type;
    QString content;
    QString created_at;

    static Message fromJson(const QJsonObject& json) {
        Message message;
        message.id = json["id"].toString().toULongLong();
        message.room_id = json["room_id"].toString().toULongLong();
        message.sender_id = json["sender_id"].toString().toULongLong();
        message.content_type = json["content_type"].toInt();
        message.content = json["content"].toString();
        message.created_at = json["created_at"].toString();
        return message;
    }
};
}  // namespace tcc::model
Q_DECLARE_METATYPE(tcc::model::Message)

#endif  // MESSAGE_H
