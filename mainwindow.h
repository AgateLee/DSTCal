#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "calculator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Calculator calc;
};

#endif // MAINWINDOW_H
