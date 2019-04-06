#include <QApplication>
#include "dbutil.h"
#include "firstwidget.h"
#include "logindialog.h"

bool login;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DBUtil dbutil = DBUtil();
    dbutil.connectDB();

    LoginDialog lg;
    Firstwidget w;

    if(lg.exec() == QDialog::Accepted)
    {
        if (login) {
            w.show();
            return a.exec();
        } else {
            QMessageBox::critical(0, QObject::tr("Login Error"),"登录失败，请检查用户名或密码");
        }
    }
    else return 0;
}


