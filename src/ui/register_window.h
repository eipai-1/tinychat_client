#ifndef REGISTER_WINDOW_H
#define REGISTER_WINDOW_H

#include <QMainWindow>

namespace Ui {
class RegisterWindow;
}

namespace tcc{
namespace ui{

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private slots:
    void onRegister();
    void onCancel();

signals:
    void registerFinished();

private:
    Ui::RegisterWindow *ui;
};

}
}
#endif // REGISTER_WINDOW_H
