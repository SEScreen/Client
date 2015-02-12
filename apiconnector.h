#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QObject>

class ApiConnector : public QObject
{
    Q_OBJECT
public:
    explicit ApiConnector(QObject *parent = 0);

signals:

public slots:

};

#endif // APICONNECTOR_H
