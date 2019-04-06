#include "mainwindow.h"
#include <QApplication>
#include "dbutil.h"

void initDB(DBUtil dbutil) {
    dbutil.initTable();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    DBUtil dbutil = DBUtil();
    dbutil.connectDB();

    w.show();

    return a.exec();
}


