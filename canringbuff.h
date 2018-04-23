#ifndef CANRINGBUFF_H
#define CANRINGBUFF_H

#include <QObject>

class canRingBuff : public QObject
{
    Q_OBJECT
public:
    explicit canRingBuff(QObject *parent = 0);

signals:

public slots:
};

#endif // CANRINGBUFF_H