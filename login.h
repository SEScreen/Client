#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
    
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    
private slots:
    void replyFinished(QNetworkReply* r);
    void on_entryButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
