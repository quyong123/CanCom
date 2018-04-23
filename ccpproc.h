#ifndef CCPPROC_H
#define CCPPROC_H

#include <QObject>
#include "ccpparam.h"


class ccpProc : public QObject
{
    Q_OBJECT
public:
    explicit ccpProc(QObject *parent = 0);
    void ccpProcRecvAck(quint8 *data);
    void ccpProcConnect(quint8 addrType,quint16 addr,quint8 *data);
    void ccpProcDisConnect(quint8 addrType,quint16 addr,quint8 *data);
    void ccpProcExchangeID(quint8 *data);
    void ccpProcSetMTA(quint8 *data,quint32 addr);
    void ccpProcUpload(quint8 *data,quint8 size);
    void ccpProcGetDAQList(quint8 *data,quint8 num);
    void ccpProcSetDAQListPtr(quint8 *data,quint8 daqListNum, quint8 ODTnum, quint8 eleNum);
    void ccpProcWriteDAQ(quint8 *data,quint8 eleSize,quint32 eleAddr);
    void ccpProcStartStop(quint8 *data,quint8 cmd,quint8 daqListnum, quint8 lastOdtnum,quint8 eventChannel,quint16 cycle);
signals:

public slots:
private:
    quint8 currendCmd;
    CCP ccpsend;
    CCP ccprecv;
};

#endif // CCPPROC_H
