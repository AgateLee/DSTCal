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

void clearLayout(QLayout* layout, bool deleteWidgets = true)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        QWidget* widget;
        if (  (deleteWidgets)
              && (widget = item->widget())  ) {
            delete widget;
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout, deleteWidgets);
        }
        delete item;
    }
}

void Firstwidget::on_pushButton_8_clicked()
{
    ui->label->setText(ui->pushButton_8->text());
    clearLayout(ui->verticalLayout_3);
    widget = new Fy();
    ui->verticalLayout_3->addWidget(widget);
}

void Firstwidget::on_pushButton_7_clicked()
{
    ui->label->setText(ui->pushButton_7->text());
    clearLayout(ui->verticalLayout_3);
    widget = new QWidget();
    ui->verticalLayout_3->addWidget(widget);
}
