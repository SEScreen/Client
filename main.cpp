#include <QApplication>
#include "main.h"
MainWindow *w;
Login *l;
QString *apikey;
ScreenDialog *sd;
ApiConnector *apicon;
#include <QStyle>
void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value){
    wid->setProperty(name,value);
    wid->style()->unpolish(wid);
    wid->style()->polish(wid);
    wid->update();
}
#include <QDesktopWidget>
#include <QFile>
#include <QUrlQuery>
#include <QMessageBox>
void showLoginFrame(){
    l->show();
    l->move(QApplication::desktop()->availableGeometry().center() - l->rect().center());
}

int main(int argc, char *argv[])
{

/*
    QUrl params;
    params.addQueryItem("apikey",apikeyC);
    QNetworkRequest req(QUrl("http://128.75.230.182:8080/login"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    req.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    manager->post(req,params.encodedQuery());
*/


//Посылаешь запрос и если есть такой, то открываешь  w->show(); если нет, то код ниже
    QApplication a(argc, argv);
    apicon=new ApiConnector();
    w=new MainWindow;
    l=new Login;
    sd=new ScreenDialog;

    QFile file("config.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray apikeyC = file.readLine();
    file.close();

    QNetworkRequest* req=new QNetworkRequest(QUrl(API_URL+"/login"));
    QUrlQuery params;
    params.addQueryItem("session_key",apikeyC);
    req->setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QNetworkReply* reply=apicon->sendHttpPost(req,params.query().toUtf8());
    apicon->connect(reply,&QNetworkReply::finished,[reply,apikeyC]{
        if(QString(reply->readAll())!=QString(apikeyC)){
            showLoginFrame();
        }});
    apicon->connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),[reply]{
        qDebug(reply->errorString().toLatin1());
        QMessageBox::critical(0,"Error","Server unavailable!");
    });


    return a.exec();
}
