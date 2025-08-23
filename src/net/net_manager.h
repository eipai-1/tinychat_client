#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <memory>
#include <stdexcept>
#include <vector>

#include <QList>
#include <QObject>
#include <QNetworkAccessManager>
#include <QFile>

#include "model/auth_model.h"
#include "model/room.h"
#include "model/message.h"
#include "net/websocket_client.h"

namespace tcc {
namespace net {

// network manager
class NetManager : public QObject {
    Q_OBJECT
public:
    static NetManager& get() {
        if (!instance_ptr_) {
            throw std::runtime_error("NetManager not initialized.");
        }
        return *instance_ptr_;
    }

    static void init() { instance_ptr_.reset(new NetManager()); }

    enum class ResType : int {
        CurUserAvatar = 1,
        UserAvatar = 2,
    };

    enum class ResResp : int {
        Success = 0,
        NotFound = 1,
    };

    void setToken(const QString& token) { token_ = token; }
    void login(const tcc::model::LoginRequest& login_req);
    void query_rooms();
    // 正常id不可能为0
    void fetch_chat_messages(u64 room_id, int limit, u64 before_id = U64_MAX);
    void fetchResouce(ResType res_type, const QString& res_path, const QString& savePath);
    WebSocketClient* websocketClient() const { return websocket_client_; }
    void connetWS(const QUrl& server_url, u64 user_id, const QString& token);

private:
    explicit NetManager(QObject* parent = nullptr);
    QNetworkAccessManager* access_manager_;
    QUrl server_url_;
    QString token_;
    WebSocketClient* websocket_client_;
    static std::unique_ptr<NetManager> instance_ptr_;
    QFile* file_;

signals:
    // login response
    void loginResp(tcc::model::LoginResp resp);
    void queryRoomsResp(std::vector<tcc::model::Room> rooms);
    void messagesFetched(const QList<tcc::model::Message>& msgs);
    void curUserAvatarFetched(bool success);
};

}  // namespace net
}  // namespace tcc
#endif  // NET_MANAGER_H
