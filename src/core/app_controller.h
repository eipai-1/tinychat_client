#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QObject>

#include "model/auth_model.h"
#include "ui/login_window.h"
#include "ui/main_window.h"
#include "ui/register_window.h"
#include "utils/deleter.h"

#include "model/user.h"

namespace tcc {
namespace core {

class AppController : public QObject {
    Q_OBJECT
public:
    explicit AppController(QObject* parent = nullptr);
    void run();

private:
    std::unique_ptr<tcc::ui::MainWindow, tcc::utils::QObjectDeleter> main_window_;
    std::unique_ptr<tcc::ui::LoginWindow, tcc::utils::QObjectDeleter> login_window_;
    std::unique_ptr<tcc::ui::RegisterWindow, tcc::utils::QObjectDeleter> register_window_;

    void showLoginWindow();
    void showMainWindow(const tcc::model::User& user);
    void showRegisterWindow();

private slots:
    void onLogin(tcc::model::LoginResp resp);
    void onLogout();
    void onRegister();
    void onRegisterFinished();

signals:
};

}  // namespace core
}  // namespace tcc
#endif  // APP_CONTROLLER_H
