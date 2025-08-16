#include "ui/main_window.h"
#include "ui_main_window.h"

#include "net/net_manager.h"
#include "model/user.h"
#include "model/room_model.h"
#include "model/room_delegate.h"

using NetManager = tcc::net::NetManager;

using Room = tcc::model::Room;
using User = tcc::model::User;
using RoomModel = tcc::model::RoomModel;
using RoomDelegate = tcc::model::RoomDelegate;

namespace tcc {
namespace ui {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    NetManager::get().query_rooms();
    // connect(ui->logout_button, &QPushButton::clicked, this, &MainWindow::logoutRequest);
    room_model_ = new RoomModel(this);
    ui->room_list_view_->setModel(room_model_);
    room_delegate_ = new RoomDelegate(this);
    ui->room_list_view_->setItemDelegate(room_delegate_);
    connect(&NetManager::get(), &NetManager::queryRoomsResp, this, &MainWindow::onQueriedRooms);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setCurrentUser(User user) {
    ui->username_label->setText(user.username);
    cur_user_ = user;
}

void MainWindow::onLogout() { emit logoutRequest(); }

void MainWindow::onQueriedRooms(std::vector<Room> rooms) {
    for (const auto &e : rooms) {
        qDebug() << "Room name:" << e.name;
        room_model_->addRoom(e);
    }
}

}  // namespace ui
}  // namespace tcc
