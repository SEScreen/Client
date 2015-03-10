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
    scene->addPixmap(sd->screen);
    connect(ui->graphicsView,SIGNAL(clicked(QMouseEvent*)),this,SLOT(onGSVclick(QMouseEvent*)));
    connectL(ui->ok,SIGNAL(clicked()),[this](){
        QPixmap image(scene->sceneRect().width(),scene->sceneRect().height());
        QPainter painter(this);
        painter.begin(&image);
        scene->render(&painter);
        painter.end();
        sd->screen=image;
    });
}

void Edit::onGSVclick(QMouseEvent *e){
    qDebug(QString::number(e->x()).toAscii());
    QPointF pt;
    pt = ui->graphicsView->mapToScene(e->pos());
    scene->clear();
    scene->addPixmap(sd->screen.copy(findWindowRect(pt.toPoint())));
    scene->setSceneRect(scene->itemsBoundingRect());

            //scene->addRect(findWindowRect(e->pos()),QPen(),QBrush(QColor(255,0,0,255)));
}

void Edit::setWindowList(WindowList list){
    this->list=list;
    int i=0;
    for(WId w:list){
        QRect r=QxtWindowSystem::windowGeometry(w);
        scene->addRect(r);
        QGraphicsTextItem *qgti=
        scene->addText(QString::number(i));
        qgti->setPos(r.center().x(),r.center().y());

        i++;
    }
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
