#include "udsform.h"
#include "ui_udsform.h"

udsForm::udsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::udsForm)
{
    ui->setupUi(this);
}

udsForm::~udsForm()
{
    delete ui;
}
