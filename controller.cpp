#include "controller.h"

Controller::Controller(DataBaseManager *db) : db(db) {

}

QStringList Controller::loadArtists() {
    return db->getArtistList();
}
QList<QPair<int, QString>> Controller::loadProjects() {
    //return db->getProjectList();
    return db->getColumnWithId("projects", "name");
}
QList<QPair<int, QString>> Controller::loadShots() {
    return db->getColumnWithId("shots", "name");
}

void Controller::storeProject(ProjectModel project) {
    db->storeProject(project);
}
