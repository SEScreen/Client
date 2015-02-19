#ifndef SCREENDIALOG_H
#define SCREENDIALOG_H

#include <QWidget>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QBuffer>
namespace Ui {
class ScreenDialog;
}

class ScreenDialog : public QWidget
{
    Q_OBJECT


public:
    explicit ScreenDialog(QWidget *parent = 0);
    ~ScreenDialog();
    void setScreen(QPixmap *grab);
    QPixmap screen;
    void send();
private slots:
    void on_imgEdit_clicked();

    void on_cancelBut_clicked();

    void on_copyButton_clicked();

    void on_uploadButton_clicked();
    void replyFinished(QNetworkReply*);

private:
    Ui::ScreenDialog *ui;
};

#endif // SCREENDIALOG_H
