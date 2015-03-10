#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QSignalMapper>
#include <functional>
class ApiConnector : public QObject
{
    Q_OBJECT
public:
    explicit ApiConnector(QObject *parent = 0);
    QNetworkReply* sendHttpGet(QNetworkRequest* req);
    QNetworkReply* sendHttpPost(QNetworkRequest* req,QByteArray params);
private:
    QNetworkAccessManager* manager;
private slots:
    void resetTimer(QTimer* timer);
};

class
        QNetworkQueryHandler : public QObject
{
    Q_OBJECT
public:
    explicit QNetworkQueryHandler(QObject *parent = 0,QNetworkReply* based=0,std::function<void()> fin=[]{},std::function<void()> err=[]{});
    QNetworkReply* on;
private:
    std::function<void()> fin;std::function<void()> err;
private slots:
    void finished();
    void errored(QNetworkReply::NetworkError);
};

#endif // APICONNECTOR_H
