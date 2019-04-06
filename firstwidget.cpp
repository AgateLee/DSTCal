#include "firstwidget.h"
#include "ui_firstwidget.h"
#include "fy.h"

Firstwidget::Firstwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Firstwidget)
{
    ui->setupUi(this);
    widget = new QWidget();
    ui->verticalLayout_3->addWidget(widget);
}

Firstwidget::~Firstwidget()
{
    delete ui;
}

void Firstwidget::on_pushButton_8_clicked()
{
    Fy * fy = new Fy();
    ui->verticalLayout_3->replaceWidget(widget, fy);
    widget = fy;
}
