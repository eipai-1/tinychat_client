#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

#include "utils/types.h"
namespace tcc {
namespace model {
struct User {
    u64 id;
    QString username;
    QString nickname;
    QString email;
    QString avatar_url;
    QString created_at;

    static User fromJson(const QJsonObject& jo) {
        return User{
            .id = jo["id"].toString().toULongLong(),
            .username = jo["username"].toString(),
            .nickname = jo["nickname"].toString(),
            .email = jo["email"].toString(),
            .avatar_url = jo["avatar_url"].toString(),
            .created_at = jo["created_at"].toString(),
        };
    }
};
}  // namespace model
}  // namespace tcc
#endif  // USER_H
