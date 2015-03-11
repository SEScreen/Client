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


void ScreenDialog::resetRect(){
    QRect r=screen.rect();
    QRect rs=ui->imgEdit->rect();
    QPixmap sc;
    ui->imgEdit->updateGeometry();
    if(r.height()>r.width()){
        sc =screen.scaledToHeight(rs.height());
    }else{
        cout<< rs.width()<<endl;
        sc =screen.scaledToWidth(rs.width());
    }
    ui->imgEdit->setPixmap(sc);
}

void ScreenDialog::setScreen(QPixmap *grab,WindowList wl){

    screen=grab->copy();
    resetRect();
    this->wl=wl;

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

    e->setWindowList(wl);
    e->beginEdit();
    e->showMaximized();
    this->hide();
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
#include <QFileDialog>
void ScreenDialog::on_saveButton_clicked()
{
    QString addr=QFileDialog::getSaveFileName(this,tr("Save path"),"",tr("Images (*.png *.jpg)"));
    QFile f( addr);

    f.open( QIODevice::WriteOnly );
    // store data in f

    screen.save(&f,addr.mid(addr.indexOf('.')+1).toLatin1().data());
    f.close();
}
