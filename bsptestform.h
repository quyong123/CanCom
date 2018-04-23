#ifndef BSPTESTFORM_H
#define BSPTESTFORM_H

#include <QWidget>

namespace Ui {
class bspTestForm;
}

class bspTestForm : public QWidget
{
    Q_OBJECT

public:
    explicit bspTestForm(QWidget *parent = 0);
    ~bspTestForm();

private:
    Ui::bspTestForm *ui;
};

#endif // BSPTESTFORM_H
