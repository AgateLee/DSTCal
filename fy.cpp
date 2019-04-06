#include "fy.h"
#include "ui_fy.h"

Fy::Fy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fy)
{
    ui->setupUi(this);
}

Fy::~Fy()
{
    delete ui;
}
