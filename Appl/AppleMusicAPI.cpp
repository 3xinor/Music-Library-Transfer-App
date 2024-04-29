//
// Created by David Exinor on 2024-04-25.
//

#include "AppleMusicAPI.h"

AppleMusicAPI::AppleMusicAPI() : WebDomainAPI() {
//TODO
// do i need to do more? who knows?
}

/* Overriding pure virtual functions to implement api specific methods used in application */

bool AppleMusicAPI::connectToCloud() {
    //TODO
    return false;
}

vector<PlayList> AppleMusicAPI::findPlayLists() {
    //TODO
    vector<PlayList> temp = {};
    return temp;
}

bool AppleMusicAPI::findSong(Song* song) {
    //TODO
    return false;
}

bool AppleMusicAPI::uploadPlaylist(PlayList playlist) {
    //TODO
    return false;
}
