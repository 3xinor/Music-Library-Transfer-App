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
    list<string> artists;
    string genre;
    string album;
    double timeLength;

public:
    // Constructor
    Song(string songName, list<string> artists, string album, string genre, double timeLength);

    // getter methods
    double getTime();
    string getName();
    list<string> getArtists();
    string getGenre();
    string getAlbum();
};


#endif //MUSIC_LIBRARY_TRANSFER_APP_SONG_H
