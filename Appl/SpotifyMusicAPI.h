//
// Created by David Exinor on 2024-04-25.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H
#define MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H

#include "WebDomainAPI.h"
struct RequestData {
    string url;
    string authorization;
    string authOptions;
};

class SpotifyMusicAPI : public WebDomainAPI {
private:
    // access token
    string userToken;
    string appToken;
    string username;
    string* spotifyAuthorizationCodePtr;
public:
    // Constructor
    SpotifyMusicAPI(string user, string* spotifyAuthorizationCodePtr);

    /* Overriding pure virtual functions to implement api specific methods used in application */
    bool connectToCloud() override;
    vector<PlayList> findPlayLists() override;
    bool findSong(Song* song) override;
    bool uploadPlaylist(PlayList playlist) override;
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_SPOTIFYMUSICAPI_H
