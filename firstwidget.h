#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>

namespace Ui {
class Firstwidget;
}

class Firstwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Firstwidget(QWidget *parent = nullptr);
    ~Firstwidget();

private:
    Ui::Firstwidget *ui;
};

#endif // FIRSTWIDGET_H
