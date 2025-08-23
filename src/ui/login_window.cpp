#include "model/auth_model.h"
#include "net/net_manager.h"
#include "ui/login_window.h"
#include "ui_login_window.h"

using LoginRequest = tcc::model::LoginRequest;
using LoginResp = tcc::model::LoginResp;
using NetManager = tcc::net::NetManager;


namespace tcc{
namespace ui{

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // 点击按钮发送登录请求
    connect(ui->login_button, &QPushButton::clicked, this, &LoginWindow::onLogin);

    // 点击按钮启动注册窗口
    connect(ui->register_button, &QPushButton::clicked, this, &LoginWindow::onRegister);

    // 登录成功时发出登录成功信号
    connect(&NetManager::get(), &NetManager::loginResp, this, &LoginWindow::onLoginSuccess);

    ui->pwd_edit->setText(QString("Alice111"));
    ui->username_edit->setText(QString("Alice"));
}

LoginWindow::~LoginWindow()
{
    qDebug("LoginWindow is being deleted...");
    delete ui;
}

void LoginWindow::onLogin()
{
    LoginRequest req{
        .username = ui->username_edit->text(),
        .password = ui->pwd_edit->text(),
    };
    NetManager::get().login(req);
    //emit loginRequest();
}

void LoginWindow::onRegister()
{
    emit registerRequest();
}

void LoginWindow::onLoginSuccess(LoginResp resp)
{
    emit loginSuccess(resp);
}

}
}
