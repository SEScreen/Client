#include "screendialog.h"
#include "ui_screendialog.h"
#include "main.h"
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
void ScreenDialog::setScreen(QPixmap *grab){
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
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}


void ScreenDialog::send(){
QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
QHttpPart textPart;
textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"apikey\""));
textPart.setBody(apikey->toLatin1());
QHttpPart imagePart;
imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"icon.png\""));
imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
QPixmap pix=screen;
QByteArray bArray;
QBuffer buffer( &bArray );
buffer.open( QIODevice::WriteOnly );
pix.save( &buffer, "PNG" );
imagePart.setBody(bArray);
multiPart->append(textPart);
multiPart->append(imagePart);
multiPart->setBoundary("boundaryHere_OOOOOO");
QNetworkRequest req(QUrl(WEB_URL+"/upload"));
QNetworkAccessManager *manager = new QNetworkAccessManager(this);
connect(manager, SIGNAL(finished(QNetworkReply*)),
this, SLOT(replyFinished(QNetworkReply*)));
QNetworkReply *rpl= manager->post(req,multiPart);
multiPart->setParent(rpl);
}


void ScreenDialog::replyFinished(QNetworkReply* r)
{
    QString str=r->readAll();
    qDebug(str.toLatin1());
    QMessageBox::information(this,"Status",str);
    QApplication::clipboard()->setText(str);
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
    qDebug("tt");
    QClipboard *cb=QApplication::clipboard();
    cb->setPixmap(screen);
}

void ScreenDialog::on_uploadButton_clicked()
{
    send();
}
