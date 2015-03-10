#include "gsc.h"

GSC::GSC(QWidget *parent) :
    QGraphicsView(parent)
{

}
void GSC::mouseReleaseEvent(QMouseEvent *event)
{
    emit clicked(event);
}
