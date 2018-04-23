#include "candevice.h"


CanDeviceParams canDevice::canDeviceParams;
VCI_BOARD_INFO canDevice::vciBoardInfo;
canDevice::canDevice(QObject *parent) : QObject(parent)
{
}

quint16 canDevice::canDeviceOpen()
{
    return VCI_OpenDevice(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,0);
}

quint16 canDevice::canDeviceClose()
{
    return VCI_CloseDevice(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex);
}

quint16 canDevice::canDeviceInit()
{
    return VCI_InitCAN(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,canDeviceParams.canDeviceNum,&canDeviceParams.canConfig);
}

quint16 canDevice::canDeviceReadBoardInfo(VCI_BOARD_INFO *vciBoardInfo)
{
    return VCI_ReadBoardInfo(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,vciBoardInfo);
}

quint16 canDevice::canDeviceClearBuffer()
{
    return VCI_ClearBuffer(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,canDeviceParams.canDeviceNum);
}

quint16 canDevice::canDeviceStartCAN()
{
    return VCI_StartCAN(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,canDeviceParams.canDeviceNum);
}

quint16 canDevice::canDeviceReceive(VCI_CAN_OBJ *RecBuff, quint16 size)
{
    return VCI_Receive(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,canDeviceParams.canDeviceNum,RecBuff,size,0);
}

quint16 canDevice::canDeviceTransmit(VCI_CAN_OBJ *SendBuff, quint16 size)
{
    return VCI_Transmit(canDeviceParams.canDeviceType,canDeviceParams.canDeviceIndex,canDeviceParams.canDeviceNum,SendBuff,size);
}

CanDeviceParams canDevice::getCanConfig()
{
    return canDeviceParams;
}

void canDevice::setCanConfig(const CanDeviceParams &value)
{
    canDeviceParams = value;
}

VCI_BOARD_INFO canDevice::getVciBoardInfo()
{
    return vciBoardInfo;
}

void canDevice::setVciBoardInfo(const VCI_BOARD_INFO &value)
{
    vciBoardInfo = value;
}

