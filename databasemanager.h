#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "models/projectmodel.h"
#include <QStringList>
/**
 * @brief The DataBaseManager class
 * provides operations to store
 * items in the data base
 * and retrieve items
 */
class DataBaseManager
{
public:
    DataBaseManager();
    QStringList getArtistList();
    QList<QPair<int, QString>> getProjectList();
    QList<QPair<int, QString>> getShotList(int show_id);
    QList<QPair<int, QString>> getColumnWithId(QString table, QString column);
    QStringList getColumn(QString table, QString column);

    void storeProject(ProjectModel project);
};

#endif // DATABASEMANAGER_H
