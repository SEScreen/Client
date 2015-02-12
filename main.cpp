#include <QApplication>
#include "main.h"

MainWindow *w;
Login *l;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   w=new MainWindow;
   l=new Login;
    l->show();
    
    return a.exec();
}
void check_user(QString login, QString password)
{
    if(login.toLatin1() == "admin" && password.toLatin1() == "258369")
    {
        l->close();
        w->show();
    }
}
