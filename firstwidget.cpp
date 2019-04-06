#include "firstwidget.h"
#include "ui_firstwidget.h"

Firstwidget::Firstwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Firstwidget)
{
    ui->setupUi(this);
}

Firstwidget::~Firstwidget()
{
    delete ui;
}
