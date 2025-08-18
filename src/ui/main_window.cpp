#include "ui/main_window.h"
#include "ui_main_window.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>

#include "net/net_manager.h"
#include "model/user.h"
#include "model/room_model.h"
#include "model/room_delegate.h"
#include "model/message_model.h"
#include "model/message.h"

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
                chat_room_mgr_->setCurRoom(room.id);
            });

    ui->chat_box_view_->setModel(chat_room_mgr_->messageModel());
    ui->chat_box_view_->setItemDelegate(chat_room_mgr_->messageDelegate());

    NetManager::get().query_rooms();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setCurrentUser(User user) {
    ui->username_label_->setText(user.username);
    cur_user_ = user;
}

void MainWindow::onLogout() { emit logoutRequest(); }

void MainWindow::onMessagesFetched(std::vector<model::Message> msgs) {
    if (msgs.empty()) {
        return;
    }
    u64 room_id = msgs[0].room_id;
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
