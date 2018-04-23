#include "ccpproc.h"

ccpProc::ccpProc(QObject *parent) : QObject(parent)
{

}

void ccpProc::ccpProcRecvAck(quint8 *data)
{
    quint8 ackType = data[0];
    quint8 ackState = data[1];
    if(ackType == 0xff)
    {
        if(ackState == 0)
        {
            if(currendCmd == CC_CONNECT)
            {

            }
        }
    }
}

void ccpProc::ccpProcConnect(quint8 addrType,quint16 addr,quint8 *data)
{
    currendCmd = CC_CONNECT;
    data[0] = CC_CONNECT;
    data[1] = 1;
    if(addrType == CCP_BROADCAST_STATION_ADDR)
    {
        data[2] = 0;
        data[3] = 0;
    }
    else
    {
        data[2] = addr&0x00ff;
        data[3] = addr >> 8;
    }
}

void ccpProc::ccpProcDisConnect(quint8 addrType, quint16 addr, quint8 *data)
{
    currendCmd = CC_DISCONNECT;
    data[0] = CC_DISCONNECT;
    data[1] = 1;
    data[2] = 0;
    if(addrType == CCP_BROADCAST_STATION_ADDR)
    {
        data[4] = 0;
        data[5] = 0;
    }
    else
    {
        data[4] = addr&0x00ff;
        data[5] = addr >> 8;
    }
}

void ccpProc::ccpProcExchangeID(quint8 *data)
{
    currendCmd = CC_EXCHANGE_ID;
    data[0] = CC_EXCHANGE_ID;
    data[1] = 1;
}

void ccpProc::ccpProcSetMTA(quint8 *data,quint32 addr)
{
    currendCmd = CC_SET_MTA;
    data[0] = CC_SET_MTA;
    data[1] = 1;
    data[2] = 0;  //MTA number
    data[3] = 0;
    data[4] = addr>>24;
    data[5] = (addr&0x00ff0000)>>16;
    data[6] = (addr&0xff00)>>8;
    data[7] = addr&0xff;
}

void ccpProc::ccpProcUpload(quint8 *data, quint8 size)
{
    currendCmd = CC_UPLOAD;
    data[0] = CC_UPLOAD;
    data[1] = 1;
    data[2] = size;  //upload size
}
void ccpProc::ccpProcGetDAQList(quint8 *data, quint8 num)
{
    currendCmd = CC_GET_DAQ_SIZE;
    data[0] = CC_GET_DAQ_SIZE;
    data[1] = 1;
    data[2] = num;  //daq list num  包含 每个list的PID 和起始的PID
}

void ccpProc::ccpProcSetDAQListPtr(quint8 *data, quint8 daqListNum, quint8 ODTnum, quint8 eleNum)
{
    currendCmd = CC_SET_DAQ_PTR;
    data[0] = CC_SET_DAQ_PTR;
    data[1] = 1;
    data[2] = daqListNum;
    data[3] = ODTnum;
    data[4] = eleNum;
}

void ccpProc::ccpProcWriteDAQ(quint8 *data, quint8 eleSize, quint32 eleAddr)
{
    currendCmd = CC_WRITE_DAQ;
    data[0] = CC_WRITE_DAQ;
    data[1] = 1;
    data[2] = eleSize;  //
    data[3] = 0;
    data[4] = eleAddr>>24;
    data[5] = (eleAddr&0x00ff0000)>>16;
    data[6] = (eleAddr&0xff00)>>8;
    data[7] = eleAddr&0xff;
}

void ccpProc::ccpProcStartStop(quint8 *data,quint8 cmd,quint8 daqListnum, quint8 lastOdtnum,quint8 eventChannel,quint16 cycle)
{
    currendCmd = CC_START_STOP;
    data[0] = CC_START_STOP;
    data[1] = 1;
    data[2] = cmd;
    data[3] = daqListnum;
    data[4] = lastOdtnum;
    data[5] = eventChannel;
    data[6] = cycle>>8;
    data[7] = cycle&0xff;
}


