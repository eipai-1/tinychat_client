#include "ui/main_window.h"
#include "ui_main_window.h"

namespace tcc{
namespace ui{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->logout_button, &QPushButton::clicked, this, &MainWindow::logoutRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLogout()
{
    emit logoutRequest();
}

}
}
