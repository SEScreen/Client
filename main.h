#include "login.h"
#include "mainwindow.h"
#include "screendialog.h"
#ifndef MAIN_H
#define MAIN_H

extern ScreenDialog *sd;
extern MainWindow *w;
extern Login *l;
extern QString *apikey;

void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value);

#endif // MAIN_H
