#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QDebug>
#include <QMessageBox>
#include "config.h"
connectDialog::connectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectDialog)
{
    ui->setupUi(this);

}
connectDialog::~connectDialog()
{
    delete ui;
}
//取消按钮
void connectDialog::on_pushButton_2_clicked()
{

    this->close();
}
//确定按钮
void connectDialog::on_pushButton_3_clicked()
{
    setCanDeviceParams();
    canDevice::setCanConfig(canDeviceParams);
    this->close();
}
//确定并打开按钮
static VCI_CAN_OBJ CANSendBuff[11];
void connectDialog::on_pushButton_clicked()
{
    VCI_BOARD_INFO vciBoardInfo;
    quint16 temp;
    setCanDeviceParams();
    canDevice::setCanConfig(canDeviceParams);
    temp = canDevice::canDeviceOpen();
    if(temp != 1)
    {
        QMessageBox::critical(this,"打开失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
    temp = canDevice::canDeviceInit();
    if(temp != 1)
    {
        QMessageBox::critical(this,"打开失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
    temp = canDevice::canDeviceReadBoardInfo(&vciBoardInfo);
    if(temp != 1)
    {
        QMessageBox::critical(this,"打开失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
    temp = canDevice::canDeviceStartCAN();
    if(temp != 1)
    {
        QMessageBox::critical(this,"打开失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
#if DEBUG_MODE
    qDebug() << "hw_Version"     << vciBoardInfo.hw_Version     << endl\
                    << "fw_Version"     << vciBoardInfo.fw_Version     << endl\
                    << "dr_Version"     << vciBoardInfo.dr_Version     << endl\
                    << "in_Version"     << vciBoardInfo.in_Version     << endl\
                    << "can_Num"        << vciBoardInfo.can_Num        << endl\
                    << "str_Serial_Num" << vciBoardInfo.str_Serial_Num << endl\
                    << "str_hw_Type"    << vciBoardInfo.str_hw_Type    << endl;
#endif
    emit connectSignal(ENSURE_AND_START_TYPE,"打开成功");
    this->close();
}

void connectDialog::setCanDeviceParams()
{
    canDeviceParams.canDeviceType = CAN_USB_DEVICE_TYPE;
    canDeviceParams.canDeviceIndex = ui->CanDeviceIndexcomboBox->currentText().toInt();
    canDeviceParams.canDeviceNum = ui->CanDeviceNumcomboBox->currentText().toInt();

    canDeviceParams.canConfig.AccCode = 0x80000000;
    canDeviceParams.canConfig.AccMask = 0xffffffff;  //接收所有的帧
    canDeviceParams.canConfig.Filter = 1;           //接收扩展帧和标准帧
    canDeviceParams.canConfig.Mode = 0 ;             //正常模式
    canDeviceParams.canConfig.Timing0 = 0x00;
    canDeviceParams.canConfig.Timing1 = 0x1C;        //默认为500k
}
