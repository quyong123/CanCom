#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
class connectDialog;
}

class connectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit connectDialog(QWidget *parent = 0);
    ~connectDialog();

private:
    Ui::connectDialog *ui;
};

#endif // CONNECTDIALOG_H
