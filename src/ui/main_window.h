#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <vector>

#include <QMainWindow>
#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QPropertyAnimation>

#include "model/user.h"
#include "model/room.h"
#include "service/chat_room_manager.h"
#include "net/net_manager.h"
#include "ui/navigation_drawer.h"

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

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void onLogout();
    void onQueriedRooms(std::vector<tcc::model::Room> rooms);
    void onMsgSendRequired(const QString& text);
    void onCurUserAvatarFetched(bool success);

    // ui slots
    void toggleNavDrawer();

signals:
    void logoutRequest();

private:
    static constexpr const char* CUR_USER_AVATAR_PATH = "/assets/images/users/avatar/";

    Ui::MainWindow* ui;
    model::User cur_user_;
    model::RoomModel* room_model_;
    model::RoomDelegate* room_delegate_;
    model::MessageModel* message_model_;
    model::MessageDelegate* message_delegate_;
    service::ChatRoomManager* chat_room_mgr_;
    QString test_text;

    // ui
    NavigationDrawer* m_nav_drawer;
    QPropertyAnimation* m_nav_drawer_anim;
};

}  // namespace ui
}  // namespace tcc
#endif  // MAIN_WINDOW_H
