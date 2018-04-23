#ifndef CANRINGBUFF_H
#define CANRINGBUFF_H

#include <QObject>
#include "candevice.h"

#define CANSENDBUFFSIZE   48
#define CANRECBUFFSIZE   48

#define RB_ERR_OK         0
#define RB_ERR_EMPTY      1
#define RB_ERR_FULL       2

typedef struct ringbuffer
{
    void *buffer;
    quint16	  read_index;
    quint16	  write_index;
    quint16	  num_used;
    quint16	  num_total;
}ringBuffer;
class canRingBuff : public QObject
{
    Q_OBJECT
public:
    explicit canRingBuff(QObject *parent = 0);
    quint16 canRingBuffInit(void *CANRecBuff);
    quint16 canRingBuffPut(void *elem,quint16 size);
    quint16 canRingBuffGet(void *elem,quint16 size);
    quint16 canRingBuffIsFull(void);
    quint16 canRingBuffIsEmpty(void);
signals:

public slots:
private:


    ringBuffer gstRingbuffer;
};

#endif // CANRINGBUFF_H
