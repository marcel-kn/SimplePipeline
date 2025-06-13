#include "controller.h"

Controller::Controller(DataBaseManager *db) : db(db) {

}

QStringList Controller::loadArtists() {
    return db->getArtistList();
}

QList<QPair<int, QString>> Controller::loadProjects() {
    return db->getColumnWithIdWhere("name", "projects");
}

QList<QPair<int, QString>> Controller::loadShots(int show_id) {
    return db->getColumnWithIdWhere("name", "shots", "show_id", show_id);
}

QList<QPair<int, QString>> Controller::loadShows() {
    return db->getColumnWithIdWhere("name", "shows");
}

void Controller::storeProject(ProjectModel project) {
    db->storeProject(project);
}
