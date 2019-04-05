#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QtDebug>

void connectDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./dst.db");
    QString path = QDir::currentPath();
    if(!db.open()) {
        qDebug() << db.lastError();
        qFatal("Failed to connect, try to init db.");
    }

    qDebug("Connected!");
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    connectDB();

    return a.exec();
}


