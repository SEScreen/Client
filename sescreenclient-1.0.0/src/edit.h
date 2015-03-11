#ifndef EDIT_H
#define EDIT_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QxtWindowSystem>
namespace Ui {
class Edit;
}

class Edit : public QWidget
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = 0);
    ~Edit();
    QGraphicsScene* scene;
    void setWindowList(WindowList list);
    WindowList list;
    QRect findWindowRect(const QPoint&);
    void closeEvent(QCloseEvent *);
    void beginEdit();

public slots:
    void onGSVclick(QMouseEvent *e);
private slots:
    void on_select_clicked();

    void on_pencil_clicked();

    void on_marker_clicked();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
