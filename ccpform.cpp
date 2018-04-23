#include "ccpform.h"
#include "ui_ccpform.h"

ccpForm::ccpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ccpForm)
{
    ui->setupUi(this);
}

ccpForm::~ccpForm()
{
    delete ui;
}
