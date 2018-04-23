#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "connectdialog.h"
#include "candevice.h"
#include "canringbuff.h"
#include "ccpform.h"
#include "bsptestform.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
private slots:
    void CANDataTimerOutSlot();
    void ConnectSlot(quint8 type,QString msg);
    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_triggered();

    void on_action_3_triggered();

    void on_actionCCP_triggered();

    void on_action_6_triggered();

private:
    Ui::MainWindow *ui;
    connectDialog *ConnectDialog;  //连接对话框
    QTimer *CANDataTimer;  //CAN数据处理的Timer
    QLabel *statusLabel;
    quint64 recvCnt;  //接收CAN帧的计数
    quint64 sendCnt;  //发送CAN帧的计数
    quint64 dataNum;
    canRingBuff CanRingBuff;
    ccpForm *CcpForm;         //ccp协议测试的窗口
    bspTestForm *BspTestForm; //硬件测试窗口的指针
    quint8 showMessageFlag;  //消息窗口是否显示的标志  显示为1 不显示为0
};

#endif // MAINWINDOW_H
