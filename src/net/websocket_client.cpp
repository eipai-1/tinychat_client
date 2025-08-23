#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>

#include "websocket_client.h"
#include "utils/enums.h"

using Message = tcc::model::Message;
using WSType = tcc::utils::WSType;

namespace tcc::net {
WebSocketClient::WebSocketClient(QObject *parent)
    : QObject{parent}, server_url_{"ws://localhost:8080"} {
    websocket_ = new QWebSocket(QString(), QWebSocketProtocol::VersionLatest, this);
    QObject::connect(websocket_, &QWebSocket::errorOccurred, this, &WebSocketClient::onSocketError);
    QObject::connect(websocket_, &QWebSocket::textMessageReceived, this,
                     &WebSocketClient::onTextMsgReceived);
    QObject::connect(websocket_, &QWebSocket::connected, this, &WebSocketClient::onConnected);
}

WebSocketClient::~WebSocketClient() {
    if (websocket_->isValid()) {
        websocket_->close();
    } else {
        qDebug() << "WebSocket is not valid, no need to close.";
    }
}

void WebSocketClient::sendChatMsg(u64 room_id, bool is_private, const QString &chat_msg) {
    QJsonObject root, data;
    if (is_private) {
        root["type"] = utils::ws_type_to_string(WSType::PrivateMsg);
    } else {
        root["type"] = utils::ws_type_to_string(WSType::GroupMsg);
    }
    data["room_id"] = QString::number(room_id);
    data["content"] = chat_msg;

    root["data"] = data;
    QJsonDocument json_doc(root);
    QString json_str = json_doc.toJson(QJsonDocument::Compact);
    sendMsg(json_str);
}

void WebSocketClient::connect(u64 cur_user_id, const QString &token) {
    qDebug() << "WebSocketClient: conneting to " << server_url_.toDisplayString();
    QNetworkRequest req(server_url_);
    req.setRawHeader(QByteArray("Authorization"), token.toUtf8());

    websocket_->open(req);
}

void WebSocketClient::sendMsg(const QString &msg) {
    if (websocket_->isValid()) {
        qDebug() << "sending msg:" << msg;
        websocket_->sendTextMessage(msg);
    } else {
        qFatal() << "WebSocket is not valid, cannot send message.";
    }
}

void WebSocketClient::onTextMsgReceived(const QString &msg) {
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON Parse Error:" << parseError.errorString();
        return;
    }
    if (!doc.isObject()) {
        qDebug() << "Received JSON is not an object.";
        return;
    }
    QJsonObject jo = doc.object();
    bool is_private = jo["type"].toString() == QString(PRVTAE_MSG_TYPE);

    Message ret_msg = Message::fromJson(jo["data"].toObject());

    emit chatMsgReceived(ret_msg);
}

void WebSocketClient::onConnected() {
    qDebug() << "ws connected";
    emit wsConnected();
}
}  // namespace tcc::net
