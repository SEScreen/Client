#include "screendialog.h"
#include "ui_screendialog.h"

ScreenDialog::ScreenDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenDialog)
{
    ui->setupUi(this);
}
#include <iostream>
using namespace std;
#include <QDesktopWidget>
void ScreenDialog::setScreen(QPixmap *grab){
    QRect r=grab->rect();
    QRect rs=ui->imgEdit->rect();
    QPixmap sc;
     ui->imgEdit->updateGeometry();
    if(r.height()>r.width()){
       sc =grab->scaledToHeight(rs.height());
    }else{
        cout<< rs.width()<<endl;
       sc =grab->scaledToWidth(rs.width());
    }

    ui->imgEdit->setPixmap(sc);
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}

ScreenDialog::~ScreenDialog()
{
    delete ui;
}

void ScreenDialog::on_imgEdit_clicked()
{

}
