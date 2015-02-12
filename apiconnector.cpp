
void login(){
        QUrl params;
        params.addQueryItem("email","example@example.com");
        params.addQueryItem("password","example");
        QNetworkRequest req(QUrl("http://localhost:8080/login"));

        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
        req.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
        QNetworkReply *rpl= manager->post(req,params.encodedQuery());

}

void send(WId frame){
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
