#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimer>
class ApiConnector : public QObject
{
    Q_OBJECT
public:
    explicit ApiConnector(QObject *parent = 0);
    QNetworkReply* sendHttpGet(QNetworkRequest* req);
private:
    QNetworkAccessManager* manager;
public slots:
private slots:
    void timedout(QTimer* timer,QNetworkReply* rep);
    void resetTimer(QTimer* timer);
};

#endif // APICONNECTOR_H
