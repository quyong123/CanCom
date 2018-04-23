#include "bsptestform.h"
#include "ui_bsptestform.h"

bspTestForm::bspTestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bspTestForm)
{
    ui->setupUi(this);
}

bspTestForm::~bspTestForm()
{
    delete ui;
}
