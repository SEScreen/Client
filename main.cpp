#include <QApplication>
#include "main.h"
MainWindow *w;
Login *l;
QString *apikey;
QString *username;
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
#include <QUrl>
#include <QMessageBox>
void showLoginFrame(){
    l->show();
    l->move(QApplication::desktop()->availableGeometry().center() - l->rect().center());
}

int main(int argc, char *argv[])
{


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
    QUrl params;
    params.addQueryItem("session_key",apikeyC);
    req->setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    QNetworkReply* reply=apicon->sendHttpPost(req,params.encodedQuery());
    new QNetworkQueryHandler(apicon,reply,[reply,apikeyC]{
        QStringList list= QString(reply->readAll()).split("\n");
        if(list[0]!=QString(apikeyC)){
            showLoginFrame();
        }else{
            username=new QString(list[1]);
            apikey=new QString(apikeyC);
            w->show();
        }
        },[reply]{
        qDebug(reply->errorString().toLatin1());
        QMessageBox::critical(0,"Error","Server unavailable!");
    });



    return a.exec();
}
