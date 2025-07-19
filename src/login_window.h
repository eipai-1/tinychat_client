#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void onLogin();
    void onRegister();

signals:
    void loginRequest();
    void registerRequest();

private:
    Ui::LoginWindow *ui;
};

#endif // LOGIN_WINDOW_H
