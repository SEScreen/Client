#include "edit.h"
#include "main.h"
#include "ui_edit.h"

Edit::Edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->addPixmap(sd->screen);

}

Edit::~Edit()
{
    delete ui;
}
