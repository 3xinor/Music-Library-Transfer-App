//
// Created by David Exinor on 2024-04-25.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H
#define MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H

#include "WebDomainAPI.h"

class SpotifyMusicAPI : public WebDomainAPI {
public:
    // Constructor
    SpotifyMusicAPI(string domain);

    /* Overriding pure virtual functions to implement api specific methods used in application */
    bool connectToCloud(string username, string password) override;
    vector<string> findPlayLists() override;
    bool getPlayList(string playList) override;
    bool findSong(Song song) override;
    bool uploadPlaylist(PlayList playlist) override;
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H
