#include "main.h"
#include "ui_login.h"
#include <QString>
#include <QMessageBox>
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
    apikey=new QString(r->readAll());
    if(*apikey!="E0"){
        l->close();
        w->show();
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
    QNetworkRequest req(QUrl("http://localhost:8080/login"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    req.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
    manager->post(req,params.encodedQuery());

}
