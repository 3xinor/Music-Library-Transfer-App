//
// Created by David Exinor on 2024-04-24.
//

#include "Converter.h"
#include "Song.h"
#include "PlayList.h"
#include "SpotifyMusicAPI.h"
#include "Server.h"
#include "User.h"

#include <iostream>

#include <chrono>
#include <thread>

int main() {

    // initialize a user
    User user1 = {};

    // initialize separate thread to run server
    string spotifyAuthorizationCode;
    int running = true;
    cout << "Initializing Server" << endl;
    thread t([&]() {
        runServer(&running, &spotifyAuthorizationCode);
    });

    cout << endl << "Please click on th below link to continue application and login within 30 seconds" << endl << endl;

    /************ initialize a spotify music object ******************/
    // spotify get request
    SpotifyMusicAPI spotifyUser = {"djez_from_the_6.1.3.", &spotifyAuthorizationCode};
    bool connectStatus = spotifyUser.connectToCloud();
    if (connectStatus) {
        // store all spotify playlists to the user object
        vector<PlayList> tempSpotifyPlaylists = spotifyUser.findPlayLists();
        user1.storePlaylists(tempSpotifyPlaylists, Platform::Spotify);

        // testing search method
         PlayList tempPlaylist = user1.getAPlaylist("Drake and Lit Fire", Platform::Spotify);
         vector<Song> tempSongs = tempPlaylist.getPlaylist();
         Song tempSong = std::move(tempSongs.back());
         bool songAvailableOnSpotify = spotifyUser.findSong(&tempSong);
         if (songAvailableOnSpotify) {
             cout << "Song: " << tempSong.getName() << " has been found on spotify with id: " << tempSong.getSpotifyURI() << endl;
         }

         // testing create playlist method
         //PlayList tempPlaylist = {"Test"};
         //spotifyUser.uploadPlaylist(tempPlaylist);
     }

     // ensure to stop server and exit program
     cout << "Stopping server" << endl;
     running = false;
     t.join();

     cout << "End of Program" << endl;
     return 0;
 }
