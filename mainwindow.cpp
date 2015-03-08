#include "main.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QDesktopWidget>
#include <QMenu>
#include <QApplication>
#ifdef USE_QXT
    #include <QxtGlobalShortcut>
#endif

void MainWindow::quit(){
    QApplication::quit();
}

void MainWindow::initMenu(){
    QAction* scr=new QAction(tr("&Screen"), this);
    connect(scr,SIGNAL(triggered()),this,SLOT(onSCH()));
    trayMenu->addAction(scr);
    QAction* quit=new QAction(tr("&Quit"), this);
    connect(quit,SIGNAL(triggered()),this,SLOT(quit()));
    trayMenu->addAction(quit);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    #ifdef USE_QXT
    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(QKeySequence(Qt::Key_Print));
    connect(shortcut,SIGNAL(activated()), this, SLOT(onSCH()));
    #endif
    trayMenu=new QMenu(this);
    initMenu();

    trayIcon=new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/res/favicon.png"));
    trayIcon->show();
    trayIcon->setToolTip("SEScreen");
    trayIcon->setContextMenu(trayMenu);

}

void MainWindow::show(){
    this->setWindowTitle(*username);
    QMainWindow::show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason){

}

void MainWindow::onSCH(){

    QPixmap grab=QPixmap::grabWindow(QApplication::desktop()->winId());


    Qt::WindowFlags eFlags = sd->windowFlags ();
    eFlags |= Qt::WindowStaysOnTopHint;
    sd->setWindowFlags(eFlags);
    sd->show();
    sd->setScreen(&grab);
    sd->setWindowState(sd->windowState() & ~Qt::WindowMinimized);
    sd->activateWindow();
    sd->raise();

}

void MainWindow::on_comboBox_activated(const QString &arg1)
{


    qDebug("132");
}
