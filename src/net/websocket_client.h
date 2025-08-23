#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QString>

#include "utils/types.h"
#include "model/message.h"

namespace tcc::net {
class WebSocketClient : public QObject {
    Q_OBJECT
public:
    explicit WebSocketClient(QObject* parent = nullptr);
    ~WebSocketClient();
    void sendChatMsg(u64 room_id, bool is_private, const QString& chat_msg);
    void connect(u64 cur_user_id, const QString& token);

private:
    QWebSocket* websocket_;
    QUrl server_url_;
    u64 cur_user_id_ = 0;
    void sendMsg(const QString& msg);

    static constexpr const char* PRVTAE_MSG_TYPE = "private_message";
    static constexpr const char* GROUP_MSG_TYPE = "group_message";

private slots:
    void onTextMsgReceived(const QString& msg);
    void onConnected();
    void onSocketError(QAbstractSocket::SocketError error) {
        qDebug() << "WebSocket Error Occurred. Code:" << error;
        qDebug() << "Error:" << websocket_->errorString();
    }

signals:
    void chatMsgReceived(const tcc::model::Message& msg);
    void wsConnected();
};
}  // namespace tcc::net

#endif  // WEBSOCKET_CLIENT_H
