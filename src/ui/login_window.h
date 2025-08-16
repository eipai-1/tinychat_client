#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>

#include "model/auth_model.h"

namespace Ui {
class LoginWindow;
}

namespace tcc{
namespace ui{

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLogin();
    void onRegister();
    void onLoginSuccess(tcc::model::LoginResp resp);

signals:
    void loginSuccess(tcc::model::LoginResp resp);
    void registerRequest();

private:
    Ui::LoginWindow *ui;
};

}
}
#endif // LOGIN_WINDOW_H
