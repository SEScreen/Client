#include "apiconnector.h"

ApiConnector::ApiConnector(QObject *parent) :
    QObject(parent)
{

    manager=new QNetworkAccessManager(this);
}

QNetworkReply* ApiConnector::sendHttpGet(QNetworkRequest *req){
    QNetworkReply *reply=manager->get(*req);
    QTimer* timer=new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(true);
    timer->start();
    connect(timer,&QTimer::timeout,[reply]{reply->abort();});
    return reply;
}


QNetworkReply* ApiConnector::sendHttpPost(QNetworkRequest *req,QByteArray params){
    QNetworkReply *reply=manager->post(*req,params);
    QTimer* timer=new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(true);
    timer->start();
    connect(timer,&QTimer::timeout,[reply]{reply->abort();});
    return reply;
}
void ApiConnector::resetTimer(QTimer *timer){
    timer->setInterval(1000);
}
