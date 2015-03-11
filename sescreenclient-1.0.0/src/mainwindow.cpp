#include "main.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QDesktopWidget>
#include <QMenu>
#include <QApplication>
#ifdef USE_QXT
    #include <QxtGlobalShortcut>
#endif
#include <QCloseEvent>
#include <QClipboard>
#include "lambdaconnect.h"
void MainWindow::rebuildMenu(){

    QAction *sett=new QAction(tr("&Settings"), this);
    connect(sett,SIGNAL(triggered()),this,SLOT(show()));

    trayMenu->addAction(sett);


    QAction* scr=new QAction(tr("&Screen"), this);
    connect(scr,SIGNAL(triggered()),this,SLOT(onSCH()));
    trayMenu->addAction(scr);
    QAction* clipB=new QAction(tr("&From Clipboard"), this);
    connectL(clipB,SIGNAL(triggered()),[]{
        QPixmap pb=QApplication::clipboard()->pixmap().copy();
        if(!pb.isNull())
        showScreenMessage(&pb);
    });
    trayMenu->addAction(clipB);
    QAction* quit=new QAction(tr("&Quit"), this);
    connectL(quit,SIGNAL(triggered()),[]{QApplication::quit();});
    trayMenu->addAction(quit);

}

void MainWindow::closeEvent(QCloseEvent * event){
    if (trayIcon->isVisible()) {
            hide();
            event->ignore();
    }
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
    rebuildMenu();

    trayIcon=new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/res/favicon.png"));
    trayIcon->show();
    trayIcon->setToolTip("SEScreen");
    trayIcon->setContextMenu(trayMenu);
    connectL(ui->exit,SIGNAL(clicked()),[](){QFile file("config.txt"); file.remove(); QApplication::exit();});
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
    showScreenMessage(&grab);
}

