#include "configuration.h"
#include "login.h"
#include "mainwindow.h"
#include "screendialog.h"
#include "apiconnector.h"


#ifndef MAIN_H
#define MAIN_H

extern ScreenDialog *sd;
extern MainWindow *w;
extern Login *l;
extern QString *apikey;
extern QString *username;
extern ApiConnector *apicon;

void setPropAndUpdate(QWidget *wid,const char *name, const QVariant &value);
void showScreenMessage(QPixmap *screen);

#endif // MAIN_H
