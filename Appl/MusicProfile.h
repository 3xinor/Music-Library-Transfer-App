//
// Created by David Exinor on 2024-04-24.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_MUSICPROFILE_H
#define MUSIC_LIBRARY_TRANSFER_APP_MUSICPROFILE_H

#include "Platforms.h"
#include "PlayList.h"

using namespace std;

class MusicProfile {
private:
    string username;
    string password;
    Platform platform;
    vector<PlayList> playLists;
public:
    MusicProfile(string username, string password, Platform platform);
    string getName();
    string getPass();
    Platform getPlatform();
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_MUSICPROFILE_H
