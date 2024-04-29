//
// Created by David Exinor on 2024-04-25.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_APPLEMUSICAPI_H
#define MUSIC_LIBRARY_TRANSFER_APP_APPLEMUSICAPI_H

#include "WebDomainAPI.h"

class AppleMusicAPI : public WebDomainAPI {
public:
    // Constructor
    AppleMusicAPI();

    /* Overriding pure virtual functions to implement api specific methods used in application */
    bool connectToCloud() override;
    vector<PlayList> findPlayLists() override;
    bool findSong(Song song) override;
    bool uploadPlaylist(PlayList playlist) override;
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_APPLEMUSICAPI_H
