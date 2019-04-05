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
    QString queryUserSQL = "SELECT name, password FROM user WHERE name = :name'";
    QString inseryUserSQL = "INSERT INTO user(name, password) VALUES (:name, :password)'";
    QString queryRefSQL = "SELECT config FROM refdata WHERE name = :name'";
    QString showSQL = "SELECT * FROM :tablename";
    QString queryConfig = "SELECT config FROM :tablename WHERE name = :name";

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
                                 "password VARCHAR,"
                                 "UNIQUE(name))")
                && query.exec("CREATE TABLE refdata("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name VARCHAR,"
                              "config VARCHAR,"
                              "UNIQUE(name))");

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

        query.prepare(queryUserSQL);
        query.bindValue(":name", username);
        if (query.exec()) {
            while(query.next()) {
                QString password = query.value(1).toString();
                if(password == MD5(pwd)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool registerUser(QString username, QString pwd) {
        QSqlQuery query;

        query.prepare(inseryUserSQL);
        query.bindValue(":name", username);
        query.bindValue(":password", MD5(pwd));
        if (query.exec()) {
            return true;
        }

        return false;
    }

    void showTable(QString tablename) {
        QSqlQuery query;

        query.prepare(showSQL);
        query.bindValue(":tablename", tablename);
        if (query.exec()) {
            query.next();
            qDebug() << query.value(0).toString().append(": ").append(query.value(1).toString());
        }
    }

    QString queryValue(QString tablename, QString name) {
        QSqlQuery query;

        query.prepare(queryConfig);
        query.bindValue(":tablename", tablename);
        query.bindValue(":name", name);
        if (query.exec()) {
            query.next();
            return query.value(0).toString();
        }

        return nullptr;
    }
};

#endif // DBUTIL_H
