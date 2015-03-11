#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSystemTrayIcon>
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
    void show();
    void closeEvent(QCloseEvent *);
private slots:
    void onSCH();
    void rebuildMenu();
    void trayActivated(QSystemTrayIcon::ActivationReason);
private:
    Ui::MainWindow *ui;
    QMenu *trayMenu;

};


#endif // MAINWINDOW_H
