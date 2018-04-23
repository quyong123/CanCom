#ifndef CANDEVICE_H
#define CANDEVICE_H

#include <QObject>
#include "ControlCAN.h"

#define CAN_USB_DEVICE_TYPE   4


typedef struct canDeviceParams{
   quint8 canDeviceType;
   quint8 canDeviceIndex;
   quint8 canDeviceNum;
   VCI_INIT_CONFIG canConfig;
}CanDeviceParams;


class canDevice : public QObject
{
    Q_OBJECT
public:
    explicit canDevice(QObject *parent = 0);
    static quint16 canDeviceOpen();

    static quint16 canDeviceClose();
    static quint16 canDeviceInit();
    static quint16 canDeviceReadBoardInfo(VCI_BOARD_INFO *vciBoardInfo);
    static quint16 canDeviceClearBuffer();
    static quint16 canDeviceStartCAN();
    static quint16 canDeviceReceive(VCI_CAN_OBJ *RecBuff,quint16 size);
    static quint16 canDeviceTransmit(VCI_CAN_OBJ *SendBuff,quint16 size);
    static CanDeviceParams getCanConfig() ;
    static void setCanConfig(const CanDeviceParams &value);

    static VCI_BOARD_INFO getVciBoardInfo() ;
    static void setVciBoardInfo(const VCI_BOARD_INFO &value);

signals:

public slots:
private:
    static CanDeviceParams canDeviceParams;
    static VCI_BOARD_INFO vciBoardInfo;
};

#endif // CANDEVICE_H
