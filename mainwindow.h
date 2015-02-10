#include <QSystemTrayIcon>
#include <QIcon>
#include <QNetworkReply>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSystemTrayIcon *trayIcon;
    QNetworkReply *reply;
    void send(WId frame);
    bool grub;
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void on_cancel_clicked();
    void replyFinished(QNetworkReply*);
    void on_send_clicked();
    void mousePressEvent(QMouseEvent * event );

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
