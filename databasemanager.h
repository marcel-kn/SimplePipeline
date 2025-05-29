#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QStringList>

class DataBaseManager
{
public:
    DataBaseManager();
    QStringList getArtistList();
    QStringList getProjectList();
    QStringList getColumn(QString table, QString column);

};

#endif // DATABASEMANAGER_H
