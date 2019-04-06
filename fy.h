#ifndef FY_H
#define FY_H

#include <QWidget>

namespace Ui {
class Fy;
}

class Fy : public QWidget
{
    Q_OBJECT

public:
    explicit Fy(QWidget *parent = nullptr);
    ~Fy();

private:
    Ui::Fy *ui;
};

#endif // FY_H
