#include "main.h"
#include "ui_login.h"
#include <QString>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}
Login::~Login()
{
    delete ui;
}
void Login::on_entryButton_clicked(){
    QString login=ui->login->text();
    QString password=ui->password->text();
    check_user(login, password);
}
