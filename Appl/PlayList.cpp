//
// Created by David Exinor on 2024-04-24.
//

#include "PlayList.h"

// Constructor definition
PlayList::PlayList(string name) {this->name = std::move(name);}

void PlayList::addSong(Song song) {
    playList.push_back(song);
}

string PlayList::getName() {return name;}

vector<Song> PlayList::getPlaylist() {return playList;}