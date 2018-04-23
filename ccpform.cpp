#include "ccpform.h"
#include "ui_ccpform.h"
#include "myhelper.h"
ccpForm::ccpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ccpForm)
{
    ui->setupUi(this);

    CanSendRingBuff.canRingBuffInit(CANSendBuff);
    CanRecvRingBuff.canRingBuffInit(CANRecBuff);
    CANSendData.DataLen = 8;
    CANSendData.ID = 0x7AA;
}

ccpForm::~ccpForm()
{
    delete ui;
}

quint16 ccpForm::ccpGetSendData(VCI_CAN_OBJ *sendData)
{
    quint16 size = 0;
    while(!CanSendRingBuff.canRingBuffGet(&sendData[size],sizeof(VCI_CAN_OBJ)))
    {
        size++;
    }
    return size;
}
//连接按钮

void ccpForm::on_connectpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcConnect(0,0,data);

    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//断开连接
void ccpForm::on_disconnectpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcDisConnect(0,0,data);

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}

void ccpForm::on_exchangeIDpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcExchangeID(data);

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}

void ccpForm::on_MTApushButton_clicked()
{
    quint8 data[8];
    //
    bool ok;
    memset(data,0,8);
    CcpProc.ccpProcSetMTA(data,ui->MTAlineEdit->text().toInt(&ok,16));
    qDebug() << "MTA" <<ui->MTAlineEdit->text().toInt(&ok,16);
    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//上传数据
void ccpForm::on_uploadpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcUpload(data, ui->uploadSizelineEdit->text().toInt());

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//获取DAQLIST的size
void ccpForm::on_daqListSizepushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcGetDAQList(data, ui->daqListNumlineEdit->text().toInt());

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//设置DAQ——List的指针
void ccpForm::on_setDaqPtrpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcSetDAQListPtr(data, ui->daqListNumlineEdit->text().toInt(),ui->OdtNumlineEdit->text().toInt(),ui->elelineEdit->text().toInt());

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//写DAQList入口
void ccpForm::on_writeDaqpushButton_clicked()
{
    quint8 data[8];
    bool ok;
    //
    memset(data,0,8);
    CcpProc.ccpProcWriteDAQ(data, ui->eleSizelineEdit->text().toInt(),ui->eleaddrlineEdit->text().toInt(&ok,16));

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}

void ccpForm::on_startpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcStartStop(data, 1,ui->startStopDaqListNumlineEdit->text().toInt(),ui->StartStopOdtNumlineEdit->text().toInt(),ui->eventChannellineEdi->text().toInt(),ui->cyclelineEdi->text().toInt());

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}

void ccpForm::on_stoppushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    CcpProc.ccpProcStartStop(data, 0,ui->startStopDaqListNumlineEdit->text().toInt(),ui->StartStopOdtNumlineEdit->text().toInt(),ui->eventChannellineEdi->text().toInt(),ui->cyclelineEdi->text().toInt());

    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
