//
// Created by David Exinor on 2024-04-29.
//

#include <iostream>
#include "User.h"

// Constructor
User::User() = default;

// store all user playlists for one specific platform
void User::storePlaylists(vector<PlayList> playlists, Platform platform) {
    switch(platform) {
        case Platform::AppleMusic:
            this->appleMusicPlaylists = std::move(playlists);
        case Platform::Spotify:
            this->spotifyPlaylists = std::move(playlists);
        case Platform::SoundCloud:
            this->soundCloudPlaylists = std::move(playlists);
        case Platform::YoutubeMusic:
            this->youtubeMusicPlaylists = std::move(playlists);
    }
}

// find a users playlist from a specific platform
PlayList User::getAPlaylist(std::string playlistName, Platform platform) {
    switch(platform) {
        case Platform::AppleMusic:
            for(auto& playlist : appleMusicPlaylists) {
                if(playlist.getName() == playlistName) {
                    return playlist;
                }
            }
        case Platform::Spotify:
            for(auto& playlist : spotifyPlaylists) {
                if(playlist.getName() == playlistName) {
                    return playlist;
                }
            }
        case Platform::SoundCloud:
            for(auto& playlist : soundCloudPlaylists) {
                if(playlist.getName() == playlistName) {
                    return playlist;
                }
            }
        case Platform::YoutubeMusic:
            for(auto& playlist : youtubeMusicPlaylists) {
                if(playlist.getName() == playlistName) {
                    return playlist;
                }
            }
        default:
            cout << "Playlist: " << playlistName << " was not found.";
            return PlayList("n/a");
    }
}