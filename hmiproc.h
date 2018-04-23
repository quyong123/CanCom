#ifndef HMIPROC_H
#define HMIPROC_H

#include <QObject>

class hmiproc : public QObject
{
    Q_OBJECT
public:
    explicit hmiproc(QObject *parent = 0);

signals:

public slots:
};

#endif // HMIPROC_H