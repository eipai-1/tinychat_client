#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QJsonObject>
#include <QVariant>

#include "utils/types.h"

namespace tcc {
namespace model {
struct Room {
    u64 id;
    int type;
    QString name;
    QString description;
    QString avatar_url;
    u64 last_message_id;
    int member_count;
    QString created_at;

    static Room fromJson(const QJsonObject& json) {
        Room room;
        room.id = json["id"].toString().toULongLong();
        room.type = json["type"].toInt();
        room.name = json["name"].toString();
        room.description = json["description"].toString();
        room.avatar_url = json["avatar_url"].toString();
        room.last_message_id = json["last_message_id"].toString().toULongLong();
        room.member_count = json["member_count"].toInt();
        room.created_at = json["created_at"].toString();
        return room;
    }
};
}  // namespace model
}  // namespace tcc
Q_DECLARE_METATYPE(tcc::model::Room)

#endif  // ROOM_H
