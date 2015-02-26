#include <QApplication>
#include "main.h"
MainWindow *w;
Login *l;
QString *apikey;
ScreenDialog *sd;
ApiConnector *apicon=new ApiConnector();
#include <QStyle>
void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value){
    wid->setProperty(name,value);
    wid->style()->unpolish(wid);
    wid->style()->polish(wid);
    wid->update();
}
#include <QDesktopWidget>
#include <QFile>
int main(int argc, char *argv[])
{
    QFile file("config.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray apikeyC = file.readLine();
    file.close();
/*
    QUrl params;
    params.addQueryItem("apikey",apikeyC);
    QNetworkRequest req(QUrl("http://128.75.230.182:8080/login"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    req.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    manager->post(req,params.encodedQuery());
*/
    QNetworkRequest* req=new QNetworkRequest(QUrl("http://128.75.230.182:8080/login"));
    apicon->sendHttpGet(req);

//Посылаешь запрос и если есть такой, то открываешь  w->show(); если нет, то код ниже
    QApplication a(argc, argv);
    w=new MainWindow;
    l=new Login;
    sd=new ScreenDialog;
    l->show();
    l->move(QApplication::desktop()->availableGeometry().center() - l->rect().center());
    return a.exec();
}
