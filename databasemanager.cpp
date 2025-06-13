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

QStringList DataBaseManager::getColumn(const QString& table, const QString& column) {
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

QList<QPair<int, QString>> DataBaseManager::getShotList(int show_id) {
    QList<QPair<int, QString>> result;
    QSqlQuery query;
    query.prepare("SELECT id, name FROM shots WHERE show_id = ?");
    query.addBindValue(show_id);

    if (!query.exec()) {
        qDebug() << "Query-Error:" << query.lastError().text();
    }
    while (query.next()){
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        result << qMakePair(id, name);
    }
    return result;
}

QList<QPair<int, QString>> DataBaseManager::getColumnWithIdWhere(
    const QString& column,
    const QString& table,
    const QString& whereColumn,
    const QVariant& whereValue)
{
    QList<QPair<int, QString>> result;
    QString queryString = QString("SELECT id, %1 FROM %2").arg(column, table);

    if (!whereColumn.isEmpty() && whereValue.isValid()) {
        queryString += QString(" WHERE %1 = ?").arg(whereColumn);
    }

    QSqlQuery query;
    query.prepare(queryString);

    if (!whereColumn.isEmpty() && whereValue.isValid()) {
        query.addBindValue(whereValue);
    }

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

void DataBaseManager::storeProject(const ProjectModel& project) {
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
