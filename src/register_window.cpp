#include "register_window.h"
#include "ui_register_window.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    connect(ui->register_button, &QPushButton::clicked, this, &RegisterWindow::onRegister);
    connect(ui->cancel_button, &QPushButton::clicked, this, &RegisterWindow::onCancel);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::onRegister()
{
    emit registerFinished();
}

void RegisterWindow::onCancel()
{
    emit registerFinished();
}
