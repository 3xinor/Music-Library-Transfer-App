//
// Created by David Exinor on 2024-04-25.
//

#include "AppleMusicAPI.h"

AppleMusicAPI::AppleMusicAPI() : WebDomainAPI() {
//TODO
// do i need to do more? who knows?
}

/* Overriding pure virtual functions to implement api specific methods used in application */

bool AppleMusicAPI::connectToCloud(std::string username, std::string password) {
    //TODO
    return false;
}

vector<string> AppleMusicAPI::findPlayLists() {
    //TODO
    vector<string> temp = {};
    return temp;
}

bool AppleMusicAPI::getPlayList(std::string playList) {
    //TODO
    return false;
}

bool AppleMusicAPI::findSong(Song song) {
    //TODO
    return false;
}

bool AppleMusicAPI::uploadPlaylist(PlayList playlist) {
    //TODO
    return false;
}
