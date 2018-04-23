#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canringbuff.h"
#include <QDebug>
#include <QMessageBox>
#include <myhelper.h>
VCI_CAN_OBJ CANRecBuff[CANRECBUFFSIZE];
VCI_CAN_OBJ CANSendBuff[CANRECBUFFSIZE];
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    recvCnt = 0;
    sendCnt = 0;
    dataNum = 0;
    showMessageFlag = 1;
    CanRingBuff.canRingBuffInit(CANSendBuff);
    ui->action_4->setEnabled(false);
    ui->action_5->setEnabled(false);
    ConnectDialog = new connectDialog(ui->centralWidget);

    statusLabel = new QLabel(this);
    statusLabel->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->statusBar->addPermanentWidget(statusLabel);

    ConnectDialog->move(this->width()/2,this->height()/2);
    ConnectDialog->setModal(true);
    ConnectDialog->show();
    connect(ConnectDialog,SIGNAL(connectSignal(quint8,QString)),this,SLOT(ConnectSlot(quint8,QString)));


    CANDataTimer = new QTimer();
    connect(CANDataTimer,SIGNAL(timeout()),this,SLOT(CANDataTimerOutSlot()));


    //
    CcpForm = new ccpForm(ui->mainwidget);
    CcpForm->hide();
    BspTestForm = new bspTestForm(ui->mainwidget);
    //ui->centralWidget->w
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ConnectDialog;
    delete CANDataTimer;
    delete BspTestForm;
}
//窗口关闭
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "程序关闭";
  //  CANDataTimer->stop();
  //  canDevice::canDeviceClose();
}

void MainWindow::CANDataTimerOutSlot()
{
    quint16 size = 0;
    size = canDevice::canDeviceReceive(CANRecBuff,10);
    QByteArray array;
    QByteArray arrayID;
    if(size != 0)
    {
        recvCnt += size;
        for(int i = 0; i < size; i++)
        {
            dataNum++;
            if(showMessageFlag == 1)
            {
                array.resize(8);
                arrayID.resize(1);
                for(quint8 j = 0; j < 8; j++)
                {
                    array[j] = CANRecBuff[i].Data[j];
                }
                arrayID[0] = CANRecBuff[i].ID;
                QString tempString = myHelper::ByteArraryToHexString(array);
                QString tempStringID = myHelper::ByteArraryToHexString(arrayID);
                ui->MessagetextBrowser->append(QString::number(dataNum)+"  接收" + "  长度 " + QString::number(CANRecBuff[i].DataLen) +" CANID: "+tempStringID+ \
                                               " 数据  " +tempString);
            }

        }
    }
    //CCP
    size  = CcpForm->ccpGetSendData(&CANSendBuff[0]);
    if(size != 0)
    {
        size = canDevice::canDeviceTransmit(&CANSendBuff[0],1);
        if(size == 0)
        {
            QMessageBox::critical(this,"发送失败","请检查链接",QMessageBox::YesAll);
            return;
        }
        else
        {
            sendCnt += size;
            for(int i = 0; i < size; i++)
            {
                dataNum++;
                if(showMessageFlag == 1)
                {
                    array.resize(8);
                    arrayID.resize(1);
                    for(quint8 j = 0; j < 8; j++)
                    {
                        array[j] = CANSendBuff[i].Data[j];
                    }
                    arrayID[0] = CANSendBuff[i].ID;
                    QString tempString = myHelper::ByteArraryToHexString(array);
                    QString tempStringID = myHelper::ByteArraryToHexString(arrayID);
                    ui->MessagetextBrowser->append(QString::number(dataNum)+"  发送" + "  长度 " + QString::number(CANSendBuff[i].DataLen) +" CANID: "+tempStringID+ \
                                                   " 数据  " +tempString);
                }
            }
        }
    }
    //
    size  = BspTestForm->ccpGetSendData(CANSendBuff);
    if(size != 0)
    {
        qDebug() << "size" << size;
        size = canDevice::canDeviceTransmit(CANSendBuff,size);
        if(size == 0)
        {
            QMessageBox::critical(this,"发送失败","请检查链接",QMessageBox::YesAll);
            return;
        }
        else
        {
            sendCnt += size;
            for(int i = 0; i < size; i++)
            {
                dataNum++;
                if(showMessageFlag == 1)
                {
                    array.resize(8);
                    arrayID.resize(1);
                    for(quint8 j = 0; j < 8; j++)
                    {
                        array[j] = CANSendBuff[i].Data[j];
                    }
                    arrayID[0] = CANSendBuff[i].ID;
                    QString tempString = myHelper::ByteArraryToHexString(array);
                    QString tempStringID = myHelper::ByteArraryToHexString(arrayID);
                    ui->MessagetextBrowser->append(QString::number(dataNum)+"  发送" + "  长度 " + QString::number(CANSendBuff[i].DataLen) +" CANID: "+tempStringID+ \
                                                   " 数据  " +tempString);
                }
            }
        }
    }
    statusLabel->setText("RecvCnt: "+QString::number(recvCnt)+" SendCnt: " + QString::number(sendCnt));
    CANDataTimer->start(5);
}

void MainWindow::ConnectSlot(quint8 type, QString msg)
{
    if(type == ENSURE_AND_START_TYPE)
    {
        CANDataTimer->start(300);
    }
    ui->statusBar->showMessage(msg);
}
//通信参数设置按钮
void MainWindow::on_action_2_triggered()
{
    ConnectDialog->setModal(true);
    ConnectDialog->show();
    CANDataTimer->stop();
}
//start
void MainWindow::on_action_4_triggered()
{
    quint16 temp;

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
    temp = canDevice::canDeviceStartCAN();
    if(temp != 1)
    {
        QMessageBox::critical(this,"打开失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
    ui->statusBar->showMessage("start");
    CANDataTimer->start(300);
}
//这个注释辅导费
void MainWindow::on_action_5_triggered()
{
    quint16 temp;
    CANDataTimer->stop();

    temp = canDevice::canDeviceClose();
    if(temp != 1)
    {
        QMessageBox::critical(this,"失败","设备不存在或者参数选择错误",QMessageBox::YesAll);
        return;
    }
    ui->statusBar->showMessage("stop");
}
//显示日志窗口
void MainWindow::on_action_triggered()
{
    ui->messagewidget->setVisible(true);
    showMessageFlag = 1;
}
//关闭显示日志窗口
void MainWindow::on_action_3_triggered()
{
    ui->messagewidget->setVisible(false);
    showMessageFlag = 0;
}
//CCP协议触发窗口
void MainWindow::on_actionCCP_triggered()
{

}
//硬件测试触发窗口
void MainWindow::on_action_6_triggered()
{

}
