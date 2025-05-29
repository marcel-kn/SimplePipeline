#include "databasemanager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QDir>

DataBaseManager::DataBaseManager() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMARIADB");
    QString configPath = QDir::homePath() + "/.simplePipeline/config.ini"; // LINUX ONLY atm
    QSettings settings(configPath, QSettings::IniFormat);
    db.setHostName(settings.value("Database/host").toString());
    db.setDatabaseName("simplePipeline");
    db.setUserName(settings.value("Database/user").toString());
    db.setPassword(settings.value("Database/password").toString());
    bool ok = db.open();
    if (!ok) {
        qDebug() << "DB is not open!";
    }
}

/**
 * @brief Returns a column of a given table as a list.
 * @param table
 * @param column
 * @return a QStringList of all entries.
 */
QStringList DataBaseManager::getColumn(QString table, QString column) {
    QStringList result;

    QString queryStr = QString("SELECT %1 FROM %2").arg(column, table);
    QSqlQuery query(queryStr);

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
    while (query.next()){
        QString entry = query.value(0).toString();
        result << entry;
    }
    return result;
}

/**
 * @brief Retrieves short names of all artists.
 * @return List of short names.
 */
QStringList DataBaseManager::getArtistList() {
    QStringList result;
    QSqlQuery query("SELECT short_name FROM artists");

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
    while (query.next()){
        QString short_name = query.value(0).toString();
        result << short_name;
    }
    return result;
}

/**
 * @brief Retrieves short names of all projects.
 * @return List of short names.
 * maybe this type of query can be made more generic
 * like getList(table, column)
 */
QStringList DataBaseManager::getProjectList() {
    QStringList result;
    QSqlQuery query("SELECT name FROM projects");

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
    while (query.next()){
        QString name = query.value(0).toString();
        result << name;
    }
    return result;
}
