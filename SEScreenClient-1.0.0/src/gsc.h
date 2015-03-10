#ifndef GSC_H
#define GSC_H

#include <QGraphicsView>

class GSC : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GSC(QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void clicked(QMouseEvent *event);
public slots:

};

#endif // GSC_H
