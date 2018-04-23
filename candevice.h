#ifndef CANDEVICE_H
#define CANDEVICE_H

#include <QObject>

class canDevice : public QObject
{
    Q_OBJECT
public:
    explicit canDevice(QObject *parent = 0);

signals:

public slots:
};

#endif // CANDEVICE_H