#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "candevice.h"

#define ENSURE_TYPE  1
#define ENSURE_AND_START_TYPE  2



namespace Ui {
class connectDialog;
}

class connectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectDialog(QWidget *parent = 0);
    ~connectDialog();

    void setCanDeviceParams();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();
signals:
    void connectSignal(quint8 type, QString msg);
private:
    Ui::connectDialog *ui;

    CanDeviceParams canDeviceParams;
};

#endif // CONNECTDIALOG_H
