#include "bsptestform.h"
#include "ui_bsptestform.h"

bspTestForm::bspTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bspTestForm)
{
    ui->setupUi(this);

    CanSendRingBuff.canRingBuffInit(CANSendBuff);
    CanRecvRingBuff.canRingBuffInit(CANRecBuff);
    CANSendData.DataLen = 8;
    CANSendData.ID = 0x3AA;

    on_tabWidget_currentChanged(1);
}

bspTestForm::~bspTestForm()
{
    delete ui;
}
quint16 bspTestForm::ccpGetSendData(VCI_CAN_OBJ *sendData)
{
    quint16 size = 0;
    if(CanSendRingBuff.canRingBuffGet(&sendData[size],sizeof(VCI_CAN_OBJ)) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//通信连接
void bspTestForm::on_connectpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 index = HMI_PRARMS_WRITE | HMI_PRARMS_TYPE_CONTROL | HMI_PRARMS_INDEX_CANSAMPLE;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = 50; //CAN采样为50ms
    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//通信断开
void bspTestForm::on_disconnectpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 index = HMI_PRARMS_WRITE | HMI_PRARMS_TYPE_CONTROL | HMI_PRARMS_INDEX_CANSAMPLE;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = 0; //CAN采样为0ms
    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//CPLD故障复位
void bspTestForm::on_cpldresetpushButton_clicked()
{
    quint8 data[8];
    //
    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_CPLD_RESET | HMI_PRARMS_TYPE_TEST;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = 1; //CAN采样为0ms
    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
//A相上管
void bspTestForm::on_checkBoxAUp_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxADown->setChecked(false);
        ui->checkBoxBDown->setChecked(false);
        ui->checkBoxBUp->setChecked(false);
        ui->checkBoxCDown->setChecked(false);
        ui->checkBoxCUp->setChecked(false);
    }
}

void bspTestForm::on_checkBoxADown_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxAUp->setChecked(false);
        ui->checkBoxBDown->setChecked(false);
        ui->checkBoxBUp->setChecked(false);
        ui->checkBoxCDown->setChecked(false);
        ui->checkBoxCUp->setChecked(false);
    }
}

//B相上管
void bspTestForm::on_checkBoxBUp_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxADown->setChecked(false);
        ui->checkBoxAUp->setChecked(false);
        ui->checkBoxBDown->setChecked(false);
        ui->checkBoxCDown->setChecked(false);
        ui->checkBoxCUp->setChecked(false);
    }
}



void bspTestForm::on_checkBoxBDown_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxADown->setChecked(false);
        ui->checkBoxAUp->setChecked(false);
        ui->checkBoxBUp->setChecked(false);
        ui->checkBoxCDown->setChecked(false);
        ui->checkBoxCUp->setChecked(false);
    }
}

void bspTestForm::on_checkBoxCUp_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxADown->setChecked(false);
        ui->checkBoxAUp->setChecked(false);
        ui->checkBoxBUp->setChecked(false);
        ui->checkBoxCDown->setChecked(false);
        ui->checkBoxBDown->setChecked(false);
    }
}

void bspTestForm::on_checkBoxCDown_clicked(bool checked)
{
    if(checked)
    {
        ui->checkBoxADown->setChecked(false);
        ui->checkBoxAUp->setChecked(false);
        ui->checkBoxBUp->setChecked(false);
        ui->checkBoxBDown->setChecked(false);
        ui->checkBoxCUp->setChecked(false);
    }
}

void bspTestForm::on_tabWidget_currentChanged(int index)
{
    quint8 data[8];
    //
    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 temp = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_MODE_CHANGE | HMI_PRARMS_TYPE_TEST;
    data[2] = temp & 0xff;
    data[3] = temp >> 8;

    switch(index)
    {
    case 0:
        data[4] = 2;
        break;
    case 1:
        data[4] = 1;
        break;
    }
    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));

}
//启动
void bspTestForm::on_startpushButton_clicked()
{
    quint8 data[8];
    //

    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 temp = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_MODE_CHANGE | HMI_PRARMS_TYPE_TEST;
    data[2] = temp & 0xff;
    data[3] = temp >> 8;

    data[4] = 1;
    memcpy(CANSendData.Data,data,8);

    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));

    memset(data,0,8);
    data[0] = HMI_SEND_FLAG;
    data[1] = HMI_SEND_FLAG;
    data[6] = HMI_SEND_FLAG;
    data[7] = HMI_SEND_FLAG;
    quint16 index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_ABC | HMI_PRARMS_TYPE_TEST;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    if(ui->checkBoxAUp->checkState() == Qt::Checked)data[4] = 1;
    else if(ui->checkBoxADown->checkState() == Qt::Checked)data[4] = 2;
    else if(ui->checkBoxBUp->checkState() == Qt::Checked)data[4] = 3;
    else if(ui->checkBoxBDown->checkState() == Qt::Checked)data[4] = 4;
    else if(ui->checkBoxCUp->checkState() == Qt::Checked)data[4] = 5;
    else if(ui->checkBoxBDown->checkState() == Qt::Checked)data[4] = 6;
    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));

     index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_PAUSE_FIRST_TIME | HMI_PRARMS_TYPE_TEST;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = ui->firstPuselineEdit->text().toInt();
    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));

     index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_PAUSE_SECOND_TIME | HMI_PRARMS_TYPE_TEST;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = ui->secondPuselineEdit->text().toInt();
    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));

     index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_PAUSE_WIDTH_TIME | HMI_PRARMS_TYPE_TEST;
    data[2] = index & 0xff;
    data[3] = index >> 8;
    data[4] = ui->betweenPuselineEdit->text().toInt();
    memcpy(CANSendData.Data,data,8);
    CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));


   index = HMI_PRARMS_WRITE | HMI_PRARMS_INDEX_PAUSE_START | HMI_PRARMS_TYPE_TEST;
   data[2] = index & 0xff;
   data[3] = index >> 8;
   data[4] = 1;
   memcpy(CANSendData.Data,data,8);
   CanSendRingBuff.canRingBuffPut(&CANSendData,sizeof(VCI_CAN_OBJ));
}
