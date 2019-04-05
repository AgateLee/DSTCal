#include "mainwindow.h"
#include <QApplication>
#include "dbutil.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DBUtil dbutil = DBUtil();

    if(dbutil.connectDB()) {

    }

    return a.exec();
}


