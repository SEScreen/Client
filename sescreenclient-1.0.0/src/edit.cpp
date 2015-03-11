#include "edit.h"
#include "main.h"
#include "ui_edit.h"
#include "lambdaconnect.h"
#include <QMouseEvent>
Edit::Edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Edit)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    connect(ui->graphicsView,SIGNAL(clicked(QMouseEvent*)),this,SLOT(onGSVclick(QMouseEvent*)));
    connectL(ui->ok,SIGNAL(clicked()),[this](){
        QPixmap image(scene->sceneRect().width(),scene->sceneRect().height());
        QPainter painter(this);
        painter.begin(&image);
        scene->render(&painter);
        painter.end();
        sd->screen=image;
        this->hide();
        sd->resetRect();
        sd->show();

    });
    connectL(ui->cancel,SIGNAL(clicked()),[this](){sd->show();this->hide();});
}


void Edit::closeEvent(QCloseEvent * event){
    sd->show();
    this->hide();
    event->ignore();
}
void Edit::beginEdit(){
    scene->clear();
    scene->addPixmap(sd->screen.copy());
    scene->setSceneRect(scene->itemsBoundingRect());

}


void Edit::onGSVclick(QMouseEvent *e){
    if(ui->graphicsView->selection){
        QPointF pt;
        pt = ui->graphicsView->mapToScene(e->pos());

        scene->clear();
        scene->addPixmap(sd->screen.copy(findWindowRect(pt.toPoint())));
        QRectF r=scene->itemsBoundingRect();
        scene->setSceneRect(r);
        ui->graphicsView->setMaximumSize(r.width(),r.height());

    }
    //scene->addRect(findWindowRect(e->pos()),QPen(),QBrush(QColor(255,0,0,255)));
}

void Edit::setWindowList(WindowList list){
    this->list=list;

}

QRect Edit::findWindowRect(const QPoint& pos)
{
    QRect result;
    for (int i = list.size() - 1; i >= 0; --i)
    {
        WId wid = list.at(i);
        if (QxtWindowSystem::windowGeometry(wid).contains(pos))
        {
            result = QxtWindowSystem::windowGeometry(wid);
            break;
        }
    }
    return result;
}

Edit::~Edit()
{
    delete ui;
}

void Edit::on_select_clicked()
{
    ui->graphicsView->selection=true;
    ui->graphicsView->pencil=false;
    ui->graphicsView->marker=false;
}

void Edit::on_pencil_clicked()
{
    ui->graphicsView->selection=false;
    ui->graphicsView->pencil=true;
    ui->graphicsView->marker=false;
}

void Edit::on_marker_clicked()
{
    ui->graphicsView->selection=false;
    ui->graphicsView->pencil=false;
    ui->graphicsView->marker=true;
}
