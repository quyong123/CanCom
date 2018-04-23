#ifndef BSPTESTFORM_H
#define BSPTESTFORM_H

#include <QWidget>
#include "canringbuff.h"
#include "hmiproc.h"
namespace Ui {
class bspTestForm;
}

class bspTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit bspTestForm(QWidget *parent = 0);
    ~bspTestForm();
    quint16 ccpGetSendData(VCI_CAN_OBJ *sendData);
private slots:
    void on_connectpushButton_clicked();

    void on_disconnectpushButton_clicked();

    void on_cpldresetpushButton_clicked();

    void on_checkBoxAUp_clicked(bool checked);

    void on_checkBoxBUp_clicked(bool checked);

    void on_checkBoxADown_clicked(bool checked);

    void on_checkBoxBDown_clicked(bool checked);

    void on_checkBoxCUp_clicked(bool checked);

    void on_checkBoxCDown_clicked(bool checked);

    void on_tabWidget_currentChanged(int index);

    void on_startpushButton_clicked();

private:
    Ui::bspTestForm *ui;
    VCI_CAN_OBJ CANSendBuff[CANSENDBUFFSIZE];
    VCI_CAN_OBJ CANRecBuff[CANRECBUFFSIZE];
    canRingBuff CanSendRingBuff;
    canRingBuff CanRecvRingBuff;
    VCI_CAN_OBJ CANSendData;
};

#endif // BSPTESTFORM_H
