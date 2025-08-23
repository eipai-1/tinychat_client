#include <memory>

#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>

#include "model/auth_model.h"
#include "model/message.h"
#include "net/net_manager.h"
#include "utils/deleter.h"
#include "utils/types.h"

using LoginRequest = tcc::model::LoginRequest;
using LoginResp = tcc::model::LoginResp;
using Room = tcc::model::Room;
using Message = tcc::model::Message;

using QObjectDeleter = tcc::utils::QObjectDeleter;

namespace tcc {
namespace net {

std::unique_ptr<NetManager> NetManager::instance_ptr_(nullptr);

NetManager::NetManager(QObject* parent)
    : QObject{parent}, server_url_("http://localhost:8080") {
    // 设置this为父对象 自动管理内存
    //websocket_client_ = new WebSocketClient(QUrl("ws://localhost:8080"), cur_user_id, this);
    access_manager_ = new QNetworkAccessManager(this);
    websocket_client_ = new WebSocketClient(this);
}

void NetManager::login(const LoginRequest& login_req) {
    QUrl url(server_url_);
    url.setPath("/api/login");

    QNetworkRequest req(url);

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_object = login_req.toJson();
    QByteArray json_data = QJsonDocument(json_object).toJson();

    QNetworkReply* reply(access_manager_->post(req, json_data));

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray json_data = reply->readAll();

            QJsonDocument json_doc = QJsonDocument::fromJson(json_data);

            if (json_doc.isNull() || !json_doc.isObject()) {
                qDebug() << "Failed to create json document or it is not a object";
                return;
            }

            QJsonObject root_jo = json_doc.object();

            LoginResp resp = LoginResp::fromJson(root_jo["data"].toObject());

            qDebug() << "Resp:\n  token:" << resp.token << "\n";
            qDebug() << "  username:" << resp.user.username << "\n";
            qDebug() << "  id:" << resp.user.id << "\n";

            net::NetManager::get().setToken(resp.token);

            emit loginResp(resp);

        } else {
            qDebug() << "Error in NetManager::login:" << reply->errorString();
            qDebug() << "Response body (if any):" << reply->readAll();
        }

        reply->deleteLater();
    });
}

void NetManager::query_rooms() {
    QUrl url(server_url_);
    url.setPath("/me/rooms");

    QNetworkRequest req(url);
    req.setRawHeader("Authorization", token_.toLocal8Bit());

    QNetworkReply* reply(access_manager_->get(req));

    connect(reply, &QNetworkReply::finished, this, [this, reply = std::move(reply)]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray json_data = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(json_data);

            if (json_doc.isNull() || !json_doc.isObject()) {
                qDebug() << "Failed to create json document or it is not a object";
                return;
            }

            QJsonObject root_jo = json_doc.object();

            std::vector<Room> rooms;

            rooms = fromJsonArray<Room>(root_jo["data"].toArray());

            emit queryRoomsResp(rooms);

        } else {
            qDebug() << "Error in NetManager::query_rooms:" << reply->errorString();
            qDebug() << "Response body (if any):" << reply->readAll();
        }

        reply->deleteLater();
    });
}

void NetManager::fetch_chat_messages(u64 room_id, int limit, u64 before_id) {
    QString path = QString("/api/rooms/%1/messages").arg(room_id);

    // 2. 使用 QUrlQuery 来构建查询参数部分 (推荐，能自动处理编码)
    QUrlQuery query;
    query.addQueryItem("limit", QString::number(limit));
    if (before_id != U64_MAX) {
        query.addQueryItem("before_id", QString::number(before_id));
    }

    // 3. 将 path 和 query 组合到 URL 上
    QUrl url(server_url_);
    url.setPath(path);
    url.setQuery(query);  // 使用 setQuery 而不是自己拼接 '?' 和 '&'

    QNetworkRequest req(url);
    req.setRawHeader("Authorization", token_.toLocal8Bit());

    QNetworkReply* reply(access_manager_->get(req));

    connect(reply, &QNetworkReply::finished, this, [this, reply = std::move(reply)]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray json_data = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(json_data);

            if (json_doc.isNull() || !json_doc.isObject()) {
                qDebug() << "Failed to create json document or it is not a object";
                return;
            }

            QJsonObject root_jo = json_doc.object();

            QList<Message> msgs;

            msgs = jsonArrayToQList<Message>(root_jo["data"].toArray());

            emit messagesFetched(msgs);

        } else {
            qDebug() << "Error in NetManager::fetch_chat_messages(u64, int):"
                     << reply->errorString();
            qDebug() << "Response body (if any):" << reply->readAll();
        }

        reply->deleteLater();
    });
}

void NetManager::connetWS(const QUrl& server_url, u64 user_id, const QString& token)
{
    websocket_client_->connect(user_id, token);
}

}  // namespace net
}  // namespace tcc
