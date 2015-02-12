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


    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}

ScreenDialog::~ScreenDialog()
{
    delete ui;
}
