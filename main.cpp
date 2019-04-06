#include <QApplication>
#include "dbutil.h"
#include "calculator.h"

void initDB(DBUtil dbutil) {
    dbutil.initTable();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DBUtil dbutil = DBUtil();
    dbutil.connectDB();

    Calculator calc;
    calc.show();

    return a.exec();
}


