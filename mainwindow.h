#include <QSystemTrayIcon>
#include <QIcon>

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
private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason);
    void on_pushButton_clicked();
 void downloadStatus();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
