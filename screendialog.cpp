#include "screendialog.h"
#include "ui_screendialog.h"
#include "main.h"
#include "lambdaconnect.h"
#include "edit.h"
#include <QxtWindowSystem>
ScreenDialog::ScreenDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenDialog)
{
    ui->setupUi(this);
}
#include <iostream>
using namespace std;
#include <QDesktopWidget>
#include <QClipboard>
#include <QMessageBox>
#include <QGraphicsTextItem>
void ScreenDialog::setScreen(QPixmap *grab){
    WindowList wl=QxtWindowSystem::windows();
    screen=grab->copy();
    QRect r=grab->rect();
    QRect rs=ui->imgEdit->rect();
    QPixmap sc;
    ui->imgEdit->updateGeometry();
    if(r.height()>r.width()){
        sc =grab->scaledToHeight(rs.height());
    }else{
        cout<< rs.width()<<endl;
        sc =grab->scaledToWidth(rs.width());
    }
    ui->imgEdit->setPixmap(sc);
    connectL(ui->imgEdit,SIGNAL(clicked()),[wl]{Edit* e=new Edit();
        int i=0;
        for(WId w:wl){
            QRect r=QxtWindowSystem::windowGeometry(w);
            e->scene->addRect(r);
            QGraphicsTextItem *qgti=
            e->scene->addText(QString::number(i));
            qgti->setPos(r.center().x(),r.center().y());

            i++;
        }
        e->show();
    });
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}


void ScreenDialog::send(){
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"apikey\""));
    textPart.setBody(apikey->toLatin1());
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"screen.png\""));
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    QPixmap pix=screen;
    QByteArray bArray;
    QBuffer buffer( &bArray );
    buffer.open( QIODevice::WriteOnly );
    pix.save( &buffer, "PNG" );
    imagePart.setBody(bArray);
    multiPart->append(textPart);
    multiPart->append(imagePart);
    QNetworkRequest req(QUrl(API_URL+"/upload"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    QNetworkReply *rpl= manager->post(req,multiPart);
    multiPart->setParent(rpl);
}




void ScreenDialog::replyFinished(QNetworkReply* r)
{
    QString str=r->readAll();
    if(str!="E0" || str!="E1"){
        QApplication::clipboard()->setText(WEB_URL+str);
        w->trayIcon->showMessage("OK!","Uploaded as "+WEB_URL+str);
    }else{
        w->trayIcon->showMessage("Hmm?!","Strange error");
    }
}

ScreenDialog::~ScreenDialog()
{
    delete ui;
}

void ScreenDialog::on_imgEdit_clicked()
{

}

void ScreenDialog::on_cancelBut_clicked()
{
    //delete screen;
    sd->close();
}

void ScreenDialog::on_copyButton_clicked()
{
    QClipboard *cb=QApplication::clipboard();
    cb->setPixmap(screen.copy());
}

void ScreenDialog::on_uploadButton_clicked()
{
    send();
}
