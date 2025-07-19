#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <QObject>

#include "ui/main_window.h"
#include "ui/login_window.h"
#include "ui/register_window.h"

namespace tcc{
namespace core {
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
    std::unique_ptr<tcc::ui::MainWindow, QObjectDeleter> main_window_;
    std::unique_ptr<tcc::ui::LoginWindow, QObjectDeleter> login_window_;
    std::unique_ptr<tcc::ui::RegisterWindow, QObjectDeleter> register_window_;

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
}
}
#endif // APP_CONTROLLER_H
