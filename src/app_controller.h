#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QObject>

#include "main_window.h"
#include "login_window.h"
#include "register_window.h"

struct QObjectDeleter {
    void operator() (QObject *obj) {
        if (obj) {
            obj->deleteLater();
        }
    }
};

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);
    void run();

private:
    std::unique_ptr<MainWindow, QObjectDeleter> main_window_;
    std::unique_ptr<LoginWindow, QObjectDeleter> login_window_;
    std::unique_ptr<RegisterWindow, QObjectDeleter> register_window_;

    void showLoginWindow();
    void showMainWindow();
    void showRegisterWindow();

private slots:
    void onLogin();
    void onLogout();
    void onRegister();
    void onRegisterFinished();

signals:
};

#endif // APP_CONTROLLER_H
