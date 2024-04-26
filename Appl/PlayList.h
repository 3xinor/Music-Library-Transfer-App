//
// Created by David Exinor on 2024-04-24.
//

#ifndef MUSIC_LIBRARY_TRANSFER_APP_PLAYLIST_H
#define MUSIC_LIBRARY_TRANSFER_APP_PLAYLIST_H

#include <vector>
#include "Song.h"

using namespace std;

class PlayList {
private:
    vector<Song> playList;
public:
    PlayList();
    void addSong(Song song);
    vector<Song> getPlaylist();
};

#endif //MUSIC_LIBRARY_TRANSFER_APP_PLAYLIST_H
