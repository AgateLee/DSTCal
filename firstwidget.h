#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>
#include "fy.h"

namespace Ui {
class Firstwidget;
}

class Firstwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Firstwidget(QWidget *parent = nullptr);
    ~Firstwidget();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Firstwidget *ui;
    QWidget * widget;
};

#endif // FIRSTWIDGET_H
