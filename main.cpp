#include <QApplication>
#include "dbutil.h"
#include "mainwindow.h"
#include "logindialog.h"

void initDB(DBUtil dbutil) {
    dbutil.initTable();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DBUtil dbutil = DBUtil();
    dbutil.connectDB();

    LoginDialog lg;
    MainWindow w;

    if(lg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else return 0;
}


