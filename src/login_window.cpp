#include "login_window.h"
#include "ui_login_window.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    connect(ui->login_button, &QPushButton::clicked, this, &LoginWindow::onLogin);
    connect(ui->register_button, &QPushButton::clicked, this, &LoginWindow::onRegister);
}

LoginWindow::~LoginWindow()
{
    qDebug("LoginWindow is being deleted...");
    delete ui;
}

void LoginWindow::onLogin()
{
    emit loginRequest();
}

void LoginWindow::onRegister()
{
    emit registerRequest();
}
