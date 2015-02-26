#include "apiconnector.h"

ApiConnector::ApiConnector(QObject *parent) :
    QObject(parent)
{
    manager=new QNetworkAccessManager(this);
}

QNetworkReply* ApiConnector::sendHttpGet(QNetworkRequest *req){
    QNetworkReply *rep=manager->get(*req);
    QTimer* timer=new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(true);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(timedout(timer,rep)));
    return rep;
}

void ApiConnector::timedout(QTimer *timer, QNetworkReply *rep){
    rep->abort();
}

void ApiConnector::resetTimer(QTimer *timer){
    timer->setInterval(1000);
}
