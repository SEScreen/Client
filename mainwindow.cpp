#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trayIcon=new QSystemTrayIcon(this);
    QIcon ico;
    ico.addFile(":/images/icon.png");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setIcon(ico);
    trayIcon->show();

}

#include <iostream>
using namespace std;
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
     case QSystemTrayIcon::DoubleClick:
         trayIcon->showMessage(trUtf8("Еба, семки есть?"),trUtf8("Я ведь и поискать могу..."),QSystemTrayIcon::Warning);
         break;
     case QSystemTrayIcon::MiddleClick:
         break;
     case QSystemTrayIcon::Context:
            exit(0);
         break;
     default:;
     }
 }
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    textPart.setBody("my text");

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\""));
    QFile *file = new QFile(":/images/icon.png");
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

    multiPart->append(textPart);
    multiPart->append(imagePart);

    QUrl url("http://128.75.230.182:8080");
    QNetworkRequest request(url);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    // here connect signals etc.
 connect(reply, SIGNAL(finished()), this, SLOT(downloadStatus()));
}
void MainWindow::downloadStatus()
{
 trayIcon->showMessage(trUtf8("Отправили"),trUtf8(""),QSystemTrayIcon::Warning);
}
