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
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void on_pushButton_clicked();
    void on_cancel_clicked();
    void replyFinished(QNetworkReply*);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
