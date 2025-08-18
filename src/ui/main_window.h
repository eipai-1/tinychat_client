#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <vector>

#include <QMainWindow>
#include <QAbstractListModel>
#include <QStyledItemDelegate>

#include "model/user.h"
#include "model/room.h"
#include "service/chat_room_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace tcc {
namespace model {
class RoomModel;
class RoomDelegate;
class MessageModel;
class MessageDelegate;
}  // namespace model

namespace ui {

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(const tcc::model::User& user, QWidget* parent = nullptr);
    ~MainWindow();
    void setCurrentUser(model::User user);

private slots:
    void onLogout();
    void onQueriedRooms(std::vector<tcc::model::Room> rooms);
    void onMessagesFetched(std::vector<tcc::model::Message> msgs);

signals:
    void logoutRequest();

private:
    Ui::MainWindow* ui;
    model::User cur_user_;
    model::RoomModel* room_model_;
    model::RoomDelegate* room_delegate_;
    model::MessageModel* message_model_;
    model::MessageDelegate* message_delegate_;
    service::ChatRoomManager* chat_room_mgr_;
};

}  // namespace ui
}  // namespace tcc
#endif  // MAIN_WINDOW_H
