#ifndef NET_MANAGER_H
#define NET_MANAGER_H

#include <memory>
#include <stdexcept>
#include <vector>

#include <QObject>
#include <QNetworkAccessManager>

#include "model/auth_model.h"
#include "model/room.h"

namespace tcc {
namespace net{

//network manager
class NetManager : public QObject
{
    Q_OBJECT
public:
    static NetManager& get() {
        if (!instance_ptr_) {
            throw std::runtime_error("NetManager not initialized.");
        }
        return *instance_ptr_;
    }

    static void init() {
        instance_ptr_.reset(new NetManager());
    }
    void setToken(const QString& token) {
        token_ = token;
    }
    void login(const tcc::model::LoginRequest& login_req);
    void query_rooms();

private:
    explicit NetManager(QObject *parent = nullptr);
    QNetworkAccessManager* access_manager_;
    QUrl server_url_;
    QString token_;

    static std::unique_ptr<NetManager> instance_ptr_;

signals:
    //login response
    void loginResp(tcc::model::LoginResp resp);
    void queryRoomsResp(std::vector<model::Room> rooms);
};

}
}
#endif // NET_MANAGER_H
