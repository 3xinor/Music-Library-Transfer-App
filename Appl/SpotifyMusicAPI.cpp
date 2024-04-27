//
// Created by David Exinor on 2024-04-25.
//

#include <random>
#include "SpotifyMusicAPI.h"

constexpr int CODE_VERIFIER_LENGTH = 128;

SpotifyMusicAPI::SpotifyMusicAPI(string domain) : WebDomainAPI(domain) {
    //TODO
    // do i need to do more? who knows?
}

/********* Spotify API specific functions *********/

/*
 * Generates and returns a PKCE compliant string
 */
string generateCodeVerifier() {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<int> dist(0, charset.size() - 1);

    string codeVerifier;
    for (int i = 0 ; i < CODE_VERIFIER_LENGTH ; ++i) {
        codeVerifier += charset[dist(gen)];
    }
    return codeVerifier;
}



/********* Overriding pure virtual functions to implement api specific methods used in application *********/

bool SpotifyMusicAPI::connectToCloud(std::string username, std::string password) {
    /*
     * Authorization code with PKCE(Proof Key for Code Exchange) Flow
     * 1. code verifier
     * 2. code challenge
     * 3. request authorization
     * 4. request an access token
     * 5. return the access token to be used elsewhere
     */

    return false;
}

vector<string> SpotifyMusicAPI::findPlayLists() {
    //TODO
    vector<string> temp = {};
    return temp;
}

bool SpotifyMusicAPI::getPlayList(std::string playList) {
    //TODO
    return false;
}

bool SpotifyMusicAPI::findSong(Song song) {
    //TODO
    return false;
}

bool SpotifyMusicAPI::uploadPlaylist(PlayList playlist) {
    //TODO
    return false;
}