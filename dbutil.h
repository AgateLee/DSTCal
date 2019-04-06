#ifndef DBUTIL_H
#define DBUTIL_H

#include <QtSql>
#include <QtDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include "initdata.h"

class DBUtil
{
private:
    QSqlDatabase db;
    QString queryUserSQL = "SELECT name, password FROM user WHERE name = :name";
    QString inseryUserSQL = "INSERT INTO user(name, password) VALUES (:name, :password)";
    QString insertConfigs = "INSERT INTO refdata(name, row, rowdata, col, coldata, config) VALUES (:name,:row, :rowdata, :col, :coldata, :config)";
    QString queryRefSQL = "SELECT config FROM refdata WHERE name = :name";
    QString showSQL = "SELECT * FROM user";
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

    bool initConfig() {
        QSqlQuery query;
        bool result = query.exec("DROP TABLE IF EXISTS refdata");
        if(!result)qDebug() << query.lastError();
        result = result
                && query.exec("CREATE TABLE refdata("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name VARCHAR,"
                              "row VARCHAR,"
                              "rowdata VARCHAR,"
                              "col VARCHAR,"
                              "coldata VARCHAR,"
                              "config VARCHAR,"
                              "UNIQUE(name))");
        if(!result)qDebug() << query.lastError();

        QByteArray buf = configs.toUtf8();
        QJsonDocument jd = QJsonDocument::fromJson(buf);
        if(jd.isObject())
        {
            QJsonObject jo = jd.object();
            QVariantMap map = jo.toVariantMap();
            foreach (QVariant entry, map) {
                query.prepare(insertConfigs);
                query.bindValue(":name",entry.toMap().value("title"));
                query.bindValue(":row",entry.toMap().value("row"));
                QJsonDocument jsonrow = QJsonDocument::fromVariant(entry.toMap().value("rowdata"));
                query.bindValue(":rowdata",jsonrow.toJson(QJsonDocument::Compact));
                query.bindValue(":col",entry.toMap().value("col"));
                QJsonDocument jsoncol = QJsonDocument::fromVariant(entry.toMap().value("coldata"));
                query.bindValue(":coldata",jsoncol.toJson(QJsonDocument::Compact));
                QJsonDocument json = QJsonDocument::fromVariant(entry.toMap().value("config"));
                query.bindValue(":config", json.toJson(QJsonDocument::Compact));
                if (!query.exec()) {
                    qDebug() << query.lastError();
                } else {
                    qDebug() << json;
                }
            }
        }
        if (!result) {
            QMessageBox::critical(0, QObject::tr("Init Database Error: "),
                                              query.lastError().text());
            return false;
        }
        return true;
    }

    bool initUser() {
        QSqlQuery query;
        bool result = query.exec("DROP TABLE IF EXISTS user");
        if(!result)qDebug() << query.lastError();
        result = result
                && query.exec("CREATE TABLE user ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "name VARCHAR,"
                                 "password VARCHAR,"
                                 "UNIQUE(name))");
        if(!result)qDebug() << query.lastError();

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
        if (username.isEmpty() || pwd.isEmpty()) {
            return false;
        }

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
        qDebug() << query.lastError();
        return false;
    }

    bool registerUser(QString username, QString pwd) {
        if (username.isEmpty() || pwd.isEmpty()) {
            return false;
        }

        QSqlQuery query;
        query.prepare(inseryUserSQL);
        query.bindValue(":name", username);
        query.bindValue(":password", MD5(pwd));
        if (query.exec()) {
            return true;
        }
        qDebug() << query.lastError();
        return false;
    }

    void showTable(QString tablename) {
        QSqlQuery query;

        query.prepare(showSQL);
        if (query.exec()) {
            while(query.next()) {
                qDebug() << query.value(0).toString().append(": ")
                            .append(query.value(1).toString()).append(": ")
                            .append(query.value(2).toString());
            }
        } else {
            qDebug() << query.lastError();
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
        qDebug() << query.lastError();
        return nullptr;
    }
};

#endif // DBUTIL_H
