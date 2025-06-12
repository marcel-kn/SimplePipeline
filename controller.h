#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QStringList>
#include "databasemanager.h"
#include "models/projectmodel.h"

class Controller
{
public:
    Controller(DataBaseManager *db);
    QStringList loadArtists();
    QList<QPair<int, QString>> loadProjects();
    QList<QPair<int, QString>> loadShots(int show_id);
    QList<QPair<int, QString>> loadShows();
    void storeProject(ProjectModel project);

private:
    DataBaseManager *db;
};


#endif // CONTROLLER_H
