//
// Created by David Exinor on 2024-04-24.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_WEBDOMAINAPI_H
#define MUSIC_LIBRARY_TRANSFER_APP_WEBDOMAINAPI_H

#define APPLEMUSICDOMAIN "AppleMusic.com"
#define SOUNDCLOUDDOMAIN "Soundcloud.com"
#define SPOTIFYDOMAIN "Spotify.com"

#include <string>
#include <vector>
#include "Song.h"
#include "PlayList.h"

using namespace std;

class WebDomainAPI {
private:
    string webDomainAPI;
public:
    WebDomainAPI(string domain);
    ~WebDomainAPI();

    /* Abstract methods to be implemented differently depending on the music platform */
    virtual bool connectToCloud(string username, string password) = 0;
    virtual vector<string> findPlayLists() = 0;
    virtual bool getPlayList(string playList) = 0;
    virtual bool findSong(Song song) = 0;
    virtual bool uploadPlaylist(PlayList playlist) = 0;
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_WEBDOMAINAPI_H
