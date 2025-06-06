#include "databasemanager.h"

#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QSettings>
#include <QFile>

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
 * @brief Retrieves entries of a specified column
 * together with their id.
 * @return List of entries and ids.
 */
QList<QPair<int, QString>> DataBaseManager::getColumnWithId(QString table, QString column) {
    QList<QPair<int, QString>> result;
    QString queryString = QString("SELECT id, %1 FROM %2").arg(column, table);
    QSqlQuery query(queryString);

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
    while (query.next()){
        int id = query.value(0).toInt();
        QString entry = query.value(1).toString();
        result << qMakePair(id, entry);
    }
    return result;
}

void DataBaseManager::storeProject(ProjectModel project) {
    QSqlQuery query;
    query.prepare("INSERT INTO projects (name, path, description, status, frameRate, resolutionW, "
                  "resolutionH) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(project.name());
    query.addBindValue(project.path());
    query.addBindValue(project.description());
    query.addBindValue(project.status());
    query.addBindValue(project.framerate());
    query.addBindValue(project.resolutionW());
    query.addBindValue(project.resolutionH());

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
}
