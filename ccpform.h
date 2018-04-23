#ifndef CCPFORM_H
#define CCPFORM_H

#include <QWidget>

namespace Ui {
class ccpForm;
}

class ccpForm : public QWidget
{
    Q_OBJECT

public:
    explicit ccpForm(QWidget *parent = 0);
    ~ccpForm();

private:
    Ui::ccpForm *ui;
};

#endif // CCPFORM_H
