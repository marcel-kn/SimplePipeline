#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QStringList>
#include "databasemanager.h"

class Controller
{
public:
    Controller(DataBaseManager *db);
    QStringList loadArtists();
    QStringList loadProjects();
    QStringList loadShots();
private:
    DataBaseManager *db;
};


#endif // CONTROLLER_H
