//
// Created by David Exinor on 2024-04-29.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_USER_H
#define MUSIC_LIBRARY_TRANSFER_APP_USER_H

#include "PlayList.h"
#include "Platforms.h"

using namespace std;

class User {
private:
    vector<PlayList> spotifyPlaylists;
    vector<PlayList> appleMusicPlaylists;
    vector<PlayList> soundCloudPlaylists;
    vector<PlayList> youtubeMusicPlaylists;

public:
    User();
    void storePlaylists(vector<PlayList>, Platform platform);
    PlayList getAPlaylist(string playlistName, Platform platform);
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_USER_H
