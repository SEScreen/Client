#include "main.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QUrl>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);
}
Login::~Login()
{
    delete ui;
}

void Login::replyFinished(QNetworkReply* r){
    QString* resp=new QString(r->readAll());
    if(*resp!="E0"){
        QStringList s=resp->split("\n");
        apikey=new QString(s[0]);
        username=new QString(s[1]);
        l->close();
        w->show();
        l->destroy();
        qDebug(apikey->toLatin1());

        QFile file("config.txt");
        file.open(QIODevice::WriteOnly);
        file.write(apikey->toLatin1());
        file.close();

    }else{
        QMessageBox::critical(this,"Error","Password or login incorrect");
    }
}

void Login::on_entryButton_clicked(){

    QString login=ui->login->text();
    QString password=ui->password->text();
    setPropAndUpdate(ui->login,"error",login=="");
    setPropAndUpdate(ui->password,"error",password=="");
    if(login=="" || password==""){
        return;
    }
    QUrl params;
    params.addQueryItem("email",login);
    params.addQueryItem("password",password);
    QNetworkRequest req(QUrl (API_URL+"/login"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    req.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    manager->post(req,params.encodedQuery());

}
