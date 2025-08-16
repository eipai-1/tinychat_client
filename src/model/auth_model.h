#ifndef AUTH_MODEL_H
#define AUTH_MODEL_H

#include <QString>
#include <QJsonObject>
#include <QVariant>

#include "model/user.h"

namespace tcc {
namespace model {

struct LoginRequest {
    QString username;
    QString password;

    QJsonObject toJson()  const {
        QJsonObject jo;
        jo["username"] = username;
        jo["password"] = password;
        return jo;
    }
};

struct LoginResp {
    QString token;
    User user;

    static LoginResp fromJson(const QJsonObject& jo) {
        return LoginResp {
            .token = jo["token"].toString(),
            .user = User::fromJson(jo["user"].toObject()),
        };
    }
};

} // namespace model
} // namespace tcc

#endif // AUTH_MODEL_H
