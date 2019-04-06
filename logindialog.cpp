#include "logindialog.h"
#include "ui_logindialog.h"
#include "dbutil.h"

extern bool login;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    DBUtil dbutil = DBUtil();
    QString username = ui->lineEdit_username->text();
    QString pwd = ui->lineEdit_pwd->text();

    login = dbutil.checkUser(username, pwd);
}

void LoginDialog::on_pushButton_register_clicked()
{
    DBUtil dbutil = DBUtil();
    QString username = ui->lineEdit_username->text();
    QString pwd = ui->lineEdit_pwd->text();

    if (dbutil.registerUser(username, pwd)) {
        QMessageBox::critical(0, QObject::tr("Register Success"),"注册成功，请登录");
    } else {
        QMessageBox::critical(0, QObject::tr("Register Fail"),"注册失败");
    }
}

void LoginDialog::on_pushButton_resetUser_clicked()
{
    DBUtil dbutil = DBUtil();
    if (dbutil.initUser()) {
        QMessageBox::critical(0, QObject::tr("InitUser Success"),"重置成功");
    } else {
        QMessageBox::critical(0, QObject::tr("InitUser Fail"),"重置失败");
    }
}

void LoginDialog::on_pushButton_resetRef_clicked()
{
    DBUtil dbutil = DBUtil();
    if (dbutil.initConfig()) {
        QMessageBox::critical(0, QObject::tr("InitConfig Success"),"重置成功");
    } else {
        QMessageBox::critical(0, QObject::tr("InitConfig Fail"),"重置失败");
    }
}
