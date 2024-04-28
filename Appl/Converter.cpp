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
    // initialize a song
    list<string> testList1 = {"Estelle", "Kanye"};
    list<string> testList2 = {"Frank Ocean"};
    Song song1 = {"American Boy", testList1, "Shine", "R&B/SOUL", 12.76};
    Song song2 = {"Chanel", testList2, "Single", "POP", 12.76};

    PlayList playlist1 = {};
    playlist1.addSong(song1);
    playlist1.addSong(song2);
    vector<Song> allSongs = playlist1.getPlaylist();

    for (size_t i = 0 ; i < allSongs.size() ; ++i) {
        cout << "Song #" << i << " " << allSongs[i].getName() << endl;
    }

    /***** initialize a spotify music object ******************/

    // initialize and start local server on port 8888 /*
    //Server server(8888);
   // server.init();
    //server.start();

    // spotify get request
    SpotifyMusicAPI spotifyUser = {};
    bool connectStatus = spotifyUser.connectToCloud("username", "password");

    //server.stop();


    return 0;
}
