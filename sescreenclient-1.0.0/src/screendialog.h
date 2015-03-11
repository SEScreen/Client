#ifndef SCREENDIALOG_H
#define SCREENDIALOG_H

#include <QWidget>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QBuffer>
#include <QxtWindowSystem>
namespace Ui {
class ScreenDialog;
}

class ScreenDialog : public QWidget
{
    Q_OBJECT


public:
    explicit ScreenDialog(QWidget *parent = 0);
    ~ScreenDialog();
    void setScreen(QPixmap *grab,WindowList wl);
    QPixmap screen;
    WindowList wl;
    void send();
    void resetRect();
private slots:

    void on_imgEdit_clicked();

    void on_cancelBut_clicked();

    void on_copyButton_clicked();

    void on_uploadButton_clicked();
    void replyFinished(QNetworkReply*);

    void on_saveButton_clicked();

private:
    Ui::ScreenDialog *ui;
};

#endif // SCREENDIALOG_H
