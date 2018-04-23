#ifndef UDSFORM_H
#define UDSFORM_H

#include <QWidget>

namespace Ui {
class udsForm;
}

class udsForm : public QWidget
{
    Q_OBJECT

public:
    explicit udsForm(QWidget *parent = 0);
    ~udsForm();

private:
    Ui::udsForm *ui;
};

#endif // UDSFORM_H
