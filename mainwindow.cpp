#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    trayIcon=new QSystemTrayIcon(this);
    QIcon ico;
    ico.addFile(":/images/icon.png");
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setIcon(ico);
    trayIcon->show();

}

#include <iostream>
using namespace std;
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
 {
     switch (reason) {
     case QSystemTrayIcon::Trigger:
     case QSystemTrayIcon::DoubleClick:
         trayIcon->showMessage(trUtf8("Еба, семки есть?"),trUtf8("Я ведь и поискать могу..."),QSystemTrayIcon::Warning);
         break;
     case QSystemTrayIcon::MiddleClick:
         break;
     case QSystemTrayIcon::Context:
            exit(0);
         break;
     default:;
     }
 }
MainWindow::~MainWindow()
{
    delete ui;
}
