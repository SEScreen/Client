#ifndef SCREENDIALOG_H
#define SCREENDIALOG_H

#include <QWidget>

namespace Ui {
class ScreenDialog;
}

class ScreenDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenDialog(QWidget *parent = 0);
    ~ScreenDialog();
    void setScreen(QPixmap *grab);

private slots:
    void on_imgEdit_clicked();

private:
    Ui::ScreenDialog *ui;
};

#endif // SCREENDIALOG_H
