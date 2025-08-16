#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <vector>

#include <QMainWindow>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

#include "model/user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#include "model/room.h"

namespace tcc {
namespace model {
class RoomModel;
class RoomDelegate;
}  // namespace model

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setCurrentUser(model::User user);

private slots:
    void onLogout();
    void onQueriedRooms(std::vector<model::Room> rooms);

signals:
    void logoutRequest();

private:
    Ui::MainWindow* ui;
    model::User cur_user_;
    model::RoomModel* room_model_;
    model::RoomDelegate* room_delegate_;
};

}  // namespace ui
}  // namespace tcc
#endif  // MAIN_WINDOW_H
