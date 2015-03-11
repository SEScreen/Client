#include "gsc.h"

GSC::GSC(QWidget *parent) :
    QGraphicsView(parent)
{

}
#include <QMouseEvent>
void GSC::mousePressEvent(QMouseEvent *event)
{
    start=event->pos();
}

void GSC::mouseMoveEvent(QMouseEvent *event){
    if(marker || pencil){
        this->scene()->addLine(QLine(mapToScene(start).toPoint(),mapToScene(event->pos()).toPoint()),marker?QPen(QBrush(QColor(46,139,87,32)),10):QPen());
        start=event->pos();
    }
}

void GSC::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked(event);
}
