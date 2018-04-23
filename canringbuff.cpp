#include "canringbuff.h"
#include <QDebug>

canRingBuff::canRingBuff(QObject *parent) : QObject(parent)
{


}

quint16 canRingBuff::canRingBuffInit(void *CANRecBuff)
{
    gstRingbuffer.buffer = (void *)CANRecBuff;
    gstRingbuffer.read_index = 0;
    gstRingbuffer.write_index = 0;
    gstRingbuffer.num_used = 0;
    gstRingbuffer.num_total = CANRECBUFFSIZE;
}

quint16 canRingBuff::canRingBuffPut(void *elem,quint16 size)
{
    int i = 0;
    unsigned char *src;
    unsigned char *dest;
    if (gstRingbuffer.num_used >= gstRingbuffer.num_total)
        return RB_ERR_FULL;

    src = (unsigned char *)elem;
    dest = (unsigned char *)gstRingbuffer.buffer + (gstRingbuffer.write_index * size);

    for (i = 0; i < size; i++)
        *dest++ = *src++;

    gstRingbuffer.write_index++;
    if (gstRingbuffer.write_index >= gstRingbuffer.num_total)
        gstRingbuffer.write_index = 0;
    gstRingbuffer.num_used++;
    return RB_ERR_OK;
}

quint16 canRingBuff::canRingBuffGet(void *elem,quint16 size)
{
    int i = 0;
    unsigned char *src;
    unsigned char *dest;
    if (gstRingbuffer.num_used <= 0)
        return RB_ERR_EMPTY;

    dest = (unsigned char *)elem;
    src = (unsigned char *)gstRingbuffer.buffer + (gstRingbuffer.read_index * size);

    for (i = 0; i < size; i++)
        *dest++ = *src++;

    gstRingbuffer.read_index++;
    if (gstRingbuffer.read_index >= gstRingbuffer.num_total)
        gstRingbuffer.read_index = 0;
    gstRingbuffer.num_used--;

    return RB_ERR_OK;
}

quint16 canRingBuff::canRingBuffIsFull()
{
    return gstRingbuffer.num_used >= gstRingbuffer.num_total;
}

quint16 canRingBuff::canRingBuffIsEmpty()
{
    return gstRingbuffer.num_used <= 0;
}
