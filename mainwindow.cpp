#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QBuffer>
#include <QDesktopWidget>
#include <QxtWindowSystem>
#include <QMouseEvent>

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

void MainWindow::send(WId frame){
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

         QHttpPart textPart;
         textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"apikey\""));
         textPart.setBody("80986588e19335c1ef1ab36066a4da4f4f71271a86ac333cded8bb27f3204ad2c963a99841a75ca1f5bea9cc2900f8cad2698630b59c43a4f497e7d217580df7");

         QHttpPart imagePart;
         imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"icon.png\""));
          imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
         QPixmap pix=QPixmap::grabWindow(frame);
         QByteArray bArray;
         QBuffer buffer( &bArray );
         buffer.open( QIODevice::WriteOnly );
         pix.save( &buffer, "PNG" );
         imagePart.setBody(bArray);

         multiPart->append(textPart);
         multiPart->append(imagePart);
        multiPart->setBoundary("boundaryHere_OOOOOO");

        QNetworkRequest req(QUrl("http://localhost:8080/upload"));

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
        QNetworkReply *rpl= manager->post(req,multiPart);
        multiPart->setParent(rpl);
}

void MainWindow::mousePressEvent(QMouseEvent* evt){
    if(grub){
        this->releaseMouse();
        grub=false;
        send(QxtWindowSystem::windowAt(this->mapToGlobal(evt->pos())));
    }
}



void MainWindow::replyFinished(QNetworkReply* r)
{
 trayIcon->showMessage(trUtf8("Отправили"),r->readAll(),QSystemTrayIcon::Warning);
}


void MainWindow::on_cancel_clicked()
{

}


void MainWindow::on_send_clicked()
{
    grub=true;
    this->grabMouse();
    /**/

}
