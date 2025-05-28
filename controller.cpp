#include "controller.h"

Controller::Controller(DataBaseManager *db) : db(db) {

}

QStringList Controller::loadArtists() {
    return db->getArtistList();
}
