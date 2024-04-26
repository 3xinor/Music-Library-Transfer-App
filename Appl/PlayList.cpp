//
// Created by David Exinor on 2024-04-24.
//

#include "PlayList.h"

// Constructor definition
PlayList::PlayList() {}

void PlayList::addSong(Song song) {
    playList.push_back(song);
}

vector<Song> PlayList::getPlaylist() {return playList;}