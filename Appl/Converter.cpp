//
// Created by David Exinor on 2024-04-24.
//

#include "Converter.h"
#include "Song.h"
#include "PlayList.h"
#include "SpotifyMusicAPI.h"
#include "Server.h"

#include <iostream>

int main() {
    /************ initialize a spotify music object ******************/
    // spotify get request
    SpotifyMusicAPI spotifyUser = {"djez_from_the_6.1.3."};
    bool connectStatus = spotifyUser.connectToCloud();
    if (connectStatus) {
        spotifyUser.findPlayLists();
    }


    return 0;
}
