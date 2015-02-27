#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QSignalMapper>
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

#endif // APICONNECTOR_H
