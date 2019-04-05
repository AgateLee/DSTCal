#include "mainwindow.h"
#include <QApplication>
#include "dbutil.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DBUtil dbutil = DBUtil();

    if(dbutil.connectDB()) {
        dbutil.initTable();
//        printf("%d", dbutil.checkUser("liyi", "123"));
//        printf("%d", dbutil.checkUser("yls", "234"));
//        dbutil.showTable("user");
    }

    return a.exec();
}


