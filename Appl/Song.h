//
// Created by David Exinor on 2024-04-24.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_SONG_H
#define MUSIC_LIBRARY_TRANSFER_APP_SONG_H

#include <list>
#include <string>

using namespace std;
class Song {
private:
    string songName;
    vector<string> artists;
    string album;
    string release;
    string spotifyURI;
    // duration in ms
    double timeLength;

public:
    // Constructor
    Song(string songName, vector<string> artists, string album, double timeLength, string release);

    // setter methods
    void setSpotifyURI(string uri);

    // getter methods
    double getTime();
    string getName();
    vector<string> getArtists();
    string getGenre();
    string getAlbum();
    string getRelease();
    string getSpotifyURI();
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_SONG_H
