#ifndef CCPFORM_H
#define CCPFORM_H

#include <QWidget>
#include "canringbuff.h"
#include "ccpproc.h"
namespace Ui {
class ccpForm;
}

class ccpForm : public QWidget
{
    Q_OBJECT

public:
    explicit ccpForm(QWidget *parent = 0);
    ~ccpForm();
    quint16 ccpGetSendData(VCI_CAN_OBJ *sendData);
private slots:
    void on_connectpushButton_clicked();

    void on_disconnectpushButton_clicked();

    void on_exchangeIDpushButton_clicked();

    void on_MTApushButton_clicked();

    void on_uploadpushButton_clicked();

    void on_daqListSizepushButton_clicked();

    void on_setDaqPtrpushButton_clicked();

    void on_writeDaqpushButton_clicked();

    void on_startpushButton_clicked();

    void on_stoppushButton_clicked();

private:
    Ui::ccpForm *ui;
    VCI_CAN_OBJ CANSendBuff[CANSENDBUFFSIZE];
    VCI_CAN_OBJ CANRecBuff[CANRECBUFFSIZE];
    canRingBuff CanSendRingBuff;
    canRingBuff CanRecvRingBuff;
    ccpProc CcpProc;
    VCI_CAN_OBJ CANSendData;
};

#endif // CCPFORM_H
