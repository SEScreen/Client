#include "screendialog.h"
#include "ui_screendialog.h"

ScreenDialog::ScreenDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenDialog)
{
    ui->setupUi(this);
}

#include <QDesktopWidget>
void ScreenDialog::setScreen(QPixmap *grab){
    QRect r=grab->rect();
    QRect rs=ui->imgEdit->rect();
    QPixmap sc;
    if(r.height()>r.width()){
       sc =grab->scaledToHeight(rs.height());
    }else{
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
