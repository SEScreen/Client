#include <QApplication>
#include "main.h"
MainWindow *w;
Login *l;
QString *apikey;

#include <QStyle>
void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value){
    wid->setProperty(name,value);
    wid->style()->unpolish(wid);
    wid->style()->polish(wid);
    wid->update();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w=new MainWindow;
    l=new Login;
    l->show();
    
    return a.exec();
}
