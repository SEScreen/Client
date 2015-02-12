#include <QApplication>
#include "main.h"
MainWindow *w;
Login *l;
QString *apikey;
ScreenDialog *sd;
#include <QStyle>
void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value){
    wid->setProperty(name,value);
    wid->style()->unpolish(wid);
    wid->style()->polish(wid);
    wid->update();
}
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w=new MainWindow;
    l=new Login;
    sd=new ScreenDialog;
    l->show();
    l->move(QApplication::desktop()->availableGeometry().center() - l->rect().center());
    return a.exec();
}
