#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "models/projectmodel.h"
#include <QStringList>
#include <QVariant>
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

    /**
     * @brief Retrieves short names of all artists.
     * @return List of short names.
     */
    QStringList getArtistList();

    QList<QPair<int, QString>> getShotList(int show_id);

    /**
     * @brief Retrieves entries of a specified column
     * together with their id (based on a column named 'id').
     * An optional WHERE column and value can be specified.
     * @return List of column entries and ids.
     */
    QList<QPair<int, QString>> getColumnWithIdWhere(
        const QString& column,
        const QString& table,
        const QString& whereColumn = QString(),
        const QVariant& whereValue = QVariant()
        );

    /**
     * @brief Returns a column of a given table as a list.
     * @param table
     * @param column
     * @return a QStringList of all entries.
     */
    QStringList getColumn(const QString& table, const QString& column);

    void storeProject(const ProjectModel& project);
};

#endif // DATABASEMANAGER_H
