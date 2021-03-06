#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_resetUser_clicked();

    void on_pushButton_resetConfig_clicked();

    void on_pushButton_query_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
