#ifndef HMIPROC_H
#define HMIPROC_H

#include <QObject>




#define HMI_PRARMS_TYPE_CONTROL 0x2000

#define HMI_PRARMS_INDEX_CANSAMPLE 998


#define HMI_PRARMS_TYPE_TEST 0x6000

#define HMI_PRARMS_INDEX_CPLD_RESET 1
#define HMI_PRARMS_INDEX_PAUSE_START 2
#define HMI_PRARMS_INDEX_PAUSE_FIRST_TIME 3
#define HMI_PRARMS_INDEX_PAUSE_SECOND_TIME 4
#define HMI_PRARMS_INDEX_ABC 5
#define HMI_PRARMS_INDEX_PAUSE_WIDTH_TIME 6
#define HMI_PRARMS_INDEX_MODE_CHANGE 7

#define HMI_PRARMS_READ 0x0000
#define HMI_PRARMS_WRITE 0x8000
#define HMI_SEND_FLAG 0xcc
#define HMI_RECV_FLAG 0xbb
class hmiproc : public QObject
{
    Q_OBJECT
public:
    explicit hmiproc(QObject *parent = 0);

signals:

public slots:
};

#endif // HMIPROC_H
