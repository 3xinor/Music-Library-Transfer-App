//
// Created by David Exinor on 2024-04-24.
//
#include <utility>
#include "Song.h"



// Constructor definition
Song::Song(string songName, list<string> artists, string album, string genre, double timeLength) {
    this->songName = std::move(songName);
    this->artists = std::move(artists);
    this->genre = std::move(genre);
    this->album = std::move(album);
    this->timeLength = timeLength;
}

// getter method definitions
double Song::getTime() { return timeLength;}
string Song::getName() {return songName;}
list<string> Song::getArtists() {return artists;}
string Song::getGenre() {return genre;}
string Song::getAlbum() {return album;}

