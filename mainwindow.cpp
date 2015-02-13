#include "main.h"
#include "ui_mainwindow.h"
#include <QShortcut>
#include <QDesktopWidget>
#include <QxtGlobalShortcut>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QxtGlobalShortcut *shortcut = new QxtGlobalShortcut(QKeySequence(Qt::Key_Print));
    connect(shortcut,SIGNAL(activated()), this, SLOT(onSCH()));
}

MainWindow::~MainWindow()
{
    delete ui;
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
