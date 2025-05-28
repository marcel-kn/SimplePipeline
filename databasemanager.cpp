#include "databasemanager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QSettings>

DataBaseManager::DataBaseManager() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMARIADB");
    QSettings settings("config.ini", QSettings::IniFormat);
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
