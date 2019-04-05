#ifndef DBUTIL_H
#define DBUTIL_H

#include <QtSql>
#include <QtDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include "dbinit.h"

class DBUtil
{
private:
    QSqlDatabase db;
    QString queryUserSQL = "SELECT name, password FROM user where name = ";
    QString queryRefSQL = "SELECT config FROM refdata where name = ";

public:
    DBUtil();

    bool connectDB() {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./dst.db");
        QString path = QDir::currentPath();
        if(!db.open()) {
            qDebug() << db.lastError();
            return false;
        }

        qDebug("Connected!");
        return true;
    }

    bool initTable() {
        QSqlQuery query;
        bool result = query.exec("DROP TABLE dst.user")
                && query.exec("DROP TABLE dst.refdata")
                && query.exec("CREATE TABLE user ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name VARCHAR,"
                                 "password VARCHAR)")
                && query.exec("CREATE TABLE refdata("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name VARCHAR,"
                              "config VARCHAR)");

        if (!result) {
            QMessageBox::critical(0, QObject::tr("Init Database Error: "),
                                              query.lastError().text());
            return false;
        }
        return true;
    }

    QString MD5(QString data) {
        QByteArray byteMd5 = QCryptographicHash::hash(data.toUtf8(),
                                                      QCryptographicHash::Md5);
        return byteMd5.toHex();
    }

    bool checkUser(QString username, QString pwd) {
        QSqlQuery query;

        query.exec(queryUserSQL.append(username).toStdString().data());
        while(query.next()) {
            QString password = query.value(1).toString();
            if(password == MD5(pwd)) {
                return true;
            }
        }

        return false;
    }


};

#endif // DBUTIL_H
