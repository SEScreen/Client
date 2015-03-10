#include "apiconnector.h"

ApiConnector::ApiConnector(QObject *parent) :
    QObject(parent)
{

    manager=new QNetworkAccessManager(this);
}

QNetworkReply* ApiConnector::sendHttpGet(QNetworkRequest *req){
    QNetworkReply *reply=manager->get(*req);

   // connect(timer,&QTimer::timeout,[reply]{reply->abort();});
    return reply;
}


QNetworkReply* ApiConnector::sendHttpPost(QNetworkRequest *req,QByteArray params){
    QNetworkReply *reply=manager->post(*req,params);

   // connect(timer,&QTimer::timeout,[reply]{reply->abort();});
    return reply;
}
void ApiConnector::resetTimer(QTimer *timer){
    timer->setInterval(1000);
}


QNetworkQueryHandler::QNetworkQueryHandler(QObject *parent,QNetworkReply* based,std::function<void()> fin,std::function<void()> err) :
    QObject(parent){
    on=based;
    this->fin=fin;
    this->err=err;
    connect(on,SIGNAL(finished()),this,SLOT(finished()));
    connect(on,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(errored(QNetworkReply::NetworkError)));
}

void QNetworkQueryHandler::finished(){
    fin();
}

void QNetworkQueryHandler::errored(QNetworkReply::NetworkError){
    err();
}
