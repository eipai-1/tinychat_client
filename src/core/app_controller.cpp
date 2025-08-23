#include "core/app_controller.h"
#include "ui/login_window.h"
#include "net/net_manager.h"
#include "model/user.h"

using LoginWindow = tcc::ui::LoginWindow;
using MainWindow = tcc::ui::MainWindow;
using RegisterWindow = tcc::ui::RegisterWindow;

using User = tcc::model::User;
using LoginResp = tcc::model::LoginResp;
using NetManager = tcc::net::NetManager;
using WebSocketClient = tcc::net::WebSocketClient;

namespace tcc {
namespace core {

AppController::AppController(QObject* parent) : QObject{parent} {}

void AppController::run() { showLoginWindow(); }

void AppController::showLoginWindow() {
    login_window_.reset(new LoginWindow());

    connect(login_window_.get(), &LoginWindow::loginSuccess, this, &AppController::onLoggedIn);
    connect(login_window_.get(), &LoginWindow::registerRequest, this, &AppController::onRegister);

    login_window_->show();
}

void AppController::showMainWindow(const tcc::model::User& user) {
    main_window_.reset(new MainWindow(user));

    connect(main_window_.get(), &MainWindow::logoutRequest, this, &AppController::onLogout);

    main_window_->show();
    login_window_ = nullptr;
}

void AppController::showRegisterWindow() {
    register_window_.reset(new RegisterWindow());

    connect(register_window_.get(), &RegisterWindow::registerFinished, this,
            &AppController::onRegisterFinished);

    register_window_->show();
}

// 登录成功时调用
void AppController::onLoggedIn(LoginResp resp) {
    connect(NetManager::get().websocketClient(), &WebSocketClient::wsConnected, this,
            &AppController::onWSConnected);
    login_resp_ = resp;
    NetManager::get().connetWS(QUrl("ws://localhost:8080"), resp.user.id, resp.token);
}

void AppController::onLogout() {
    main_window_.reset();

    showLoginWindow();
}

void AppController::onRegister() {
    login_window_.reset();

    showRegisterWindow();
}

void AppController::onRegisterFinished() {
    register_window_.reset();

    showLoginWindow();
}

void AppController::onWSConnected() { showMainWindow(login_resp_.user); }

}  // namespace core
}  // namespace tcc
