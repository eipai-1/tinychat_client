#include "ui/main_window.h"
#include "ui_main_window.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QUrl>
#include <QQmlContext>
#include <QPixmap>

#include "net/net_manager.h"
#include "model/user.h"
#include "model/room_model.h"
#include "model/room_delegate.h"
#include "model/message_model.h"
#include "model/message.h"
#include "ui/chat_msg_edit.h"
#include "utils/enums.h"

using NetManager = tcc::net::NetManager;

using Room = tcc::model::Room;
using User = tcc::model::User;
using RoomModel = tcc::model::RoomModel;
using RoomDelegate = tcc::model::RoomDelegate;
using MessageModel = tcc::model::MessageModel;
using Message = tcc::model::Message;
using ChatRoomManager = tcc::service::ChatRoomManager;

#include <QListView>
#include <QItemSelectionModel>

namespace tcc {
namespace ui {
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {}

MainWindow::MainWindow(const tcc::model::User& user, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), cur_user_{user} {
    ui->setupUi(this);

    connect(ui->chat_msg_edit_, &ChatMsgEdit::ctrlEnterPressed, this,
            &MainWindow::onMsgSendRequired);
    connect(&NetManager::get(), &NetManager::queryRoomsResp, this, &MainWindow::onQueriedRooms);

    // connect(ui->logout_button, &QPushButton::clicked, this, &MainWindow::logoutRequest);
    chat_room_mgr_ = new ChatRoomManager(this, user.id);
    room_model_ = new RoomModel(this);
    ui->room_list_view_->setModel(room_model_);
    room_delegate_ = new RoomDelegate(this);
    ui->room_list_view_->setItemDelegate(room_delegate_);
    // ui->room_list_view_->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->room_list_view_->selectionModel(), &QItemSelectionModel::selectionChanged, this,
            [this](const QItemSelection& selected, const QItemSelection& deselected) {
                if (selected.indexes().isEmpty()) {
                    return;
                }
                QModelIndex selectedIdx = selected.indexes().first();
                Room room =
                    selectedIdx.data(static_cast<int>(RoomModel::Role::Complete)).value<Room>();
                qDebug() << "选中:" << room.name;
                // NetManager::get().fetch_chat_messages(room.id, 50);
                chat_room_mgr_->setCurRoom(room.id, static_cast<Room::Type>(room.type));
            });
    ui->room_list_view_->setMinimumWidth(60);

    // ui->username_label_->setText(cur_user_.username);

    ui->chat_msg_edit_->resize(100, 80);

    ui->chat_box_widget_->setMinimumWidth(150);
    ui->chat_box_widget_->rootContext()->setContextProperty("messageModel",
                                                            chat_room_mgr_->messageModel());
    ui->chat_box_widget_->setSource(QUrl("qrc:/qml/chat_box_widget.qml"));
    ui->chat_box_widget_->show();

    connect(&NetManager::get(), &NetManager::curUserAvatarFetched, this,
            &MainWindow::onCurUserAvatarFetched);

    // ui
    m_nav_drawer = new NavigationDrawer(this);
    m_nav_drawer_anim = new QPropertyAnimation(m_nav_drawer, "expansionProgress", this);
    m_nav_drawer_anim->setDuration(250);
    m_nav_drawer_anim->setEasingCurve(QEasingCurve::OutCubic);
    connect(ui->m_toggle_nav_drawer_btn, &QPushButton::clicked, this, &MainWindow::toggleNavDrawer);
    connect(ui->toggle, &QPushButton::clicked, this, &MainWindow::toggleNavDrawer);

    // current user avatar request path
    QString cur_user_avatar_rp = "/images/users/avatar/" + QString::number(cur_user_.id) + ".jpg";

    // current user avatar save path
    QString cur_user_avatar_sp =
        utils::working_dir() + CUR_USER_AVATAR_PATH + QString::number(cur_user_.id) + ".jpg";
    NetManager::get().query_rooms();
    NetManager::get().fetchResouce(NetManager::ResType::CurUserAvatar, cur_user_avatar_rp,
                                   cur_user_avatar_sp);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setCurrentUser(User user) {
    // ui->username_label_->setText(user.username);
    cur_user_ = user;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    m_nav_drawer->adjustSize();
}

void MainWindow::onLogout() { emit logoutRequest(); }

void MainWindow::onMsgSendRequired(const QString& text) {
    qDebug() << "msg send required:" << text;
    NetManager::get().websocketClient()->sendChatMsg(
        chat_room_mgr_->curRoomId(), chat_room_mgr_->curRoomType() == Room::Type::Private, text);
}

void MainWindow::onCurUserAvatarFetched(bool success) {
    if (!success) {
        ui->avatar_label_->setPixmap(
            QPixmap("://icons/error-icon.png")
                .scaled(45, 45, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        return;
    }
    QString save_path =
        utils::working_dir() + CUR_USER_AVATAR_PATH + QString::number(cur_user_.id) + ".jpg";
    ui->avatar_label_->setPixmap(
        QPixmap(save_path).scaled(45, 45, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::toggleNavDrawer() {
    if (m_nav_drawer->isExpanded()) {
        m_nav_drawer->setExpanded(false);
        m_nav_drawer_anim->stop();
        m_nav_drawer_anim->setStartValue(m_nav_drawer->expansionProgress());
        m_nav_drawer_anim->setEndValue(0.0);
        m_nav_drawer_anim->start();
    } else {
        m_nav_drawer->setExpanded(true);
        m_nav_drawer_anim->stop();
        m_nav_drawer_anim->setStartValue(m_nav_drawer->expansionProgress());
        m_nav_drawer_anim->setEndValue(1.0);
        m_nav_drawer_anim->start();
    }
}

void MainWindow::onQueriedRooms(std::vector<Room> rooms) {
    for (const auto& e : rooms) {
        qDebug() << "Room name:" << e.name;
        room_model_->addRoom(e);
        NetManager::get().fetch_chat_messages(e.id, 50);
    }
}

}  // namespace ui
}  // namespace tcc
