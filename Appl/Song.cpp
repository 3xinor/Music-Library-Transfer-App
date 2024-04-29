//
// Created by David Exinor on 2024-04-24.
//
#include <utility>
#include "Song.h"



// Constructor definition
Song::Song(string songName, vector<string> artists, string album, double timeLength, string release) {
    this->songName = std::move(songName);
    this->artists = std::move(artists);
    this->album = std::move(album);
    this->release = std::move(release);
    this->timeLength = timeLength;
}

// getter method definitions
double Song::getTime() { return timeLength;}
string Song::getName() {return songName;}
vector<string> Song::getArtists() {return artists;}
string Song::getAlbum() {return album;}
string Song::getRelease() {return release;}

