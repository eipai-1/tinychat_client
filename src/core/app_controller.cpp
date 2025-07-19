#include "core/app_controller.h"
#include "ui/login_window.h"

using LoginWindow = tcc::ui::LoginWindow;
using MainWindow = tcc::ui::MainWindow;
using RegisterWindow = tcc::ui::RegisterWindow;

namespace tcc{
namespace core{

AppController::AppController(QObject *parent)
    : QObject{parent}
{
}

void AppController::run()
{
    showLoginWindow();
}

void AppController::showLoginWindow()
{
    login_window_.reset(new LoginWindow());

    connect(login_window_.get(), &LoginWindow::loginRequest,
            this, &AppController::onLogin);
    connect(login_window_.get(), &LoginWindow::registerRequest,
            this, &AppController::onRegister);

    login_window_->show();
}

void AppController::showMainWindow()
{
    main_window_.reset(new MainWindow());

    connect(main_window_.get(), &MainWindow::logoutRequest,
            this, &AppController::onLogout);

    main_window_->show();
}

void AppController::showRegisterWindow()
{
    register_window_.reset(new RegisterWindow());

    connect(register_window_.get(), &RegisterWindow::registerFinished, this,
            &AppController::onRegisterFinished);

    register_window_->show();
}

void AppController::onLogin()
{
    login_window_.reset();

    showMainWindow();
}

void AppController::onLogout()
{
    main_window_.reset();

    showLoginWindow();
}

void AppController::onRegister()
{
    login_window_.reset();

    showRegisterWindow();
}

void AppController::onRegisterFinished()
{
    register_window_.reset();

    showLoginWindow();
}

}
}
