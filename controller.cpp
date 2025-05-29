#include "controller.h"

Controller::Controller(DataBaseManager *db) : db(db) {

}

QStringList Controller::loadArtists() {
    return db->getArtistList();
}
QStringList Controller::loadProjects() {
    return db->getProjectList();
}
QStringList Controller::loadShots() {
    return db->getColumn("shots", "name");
}
