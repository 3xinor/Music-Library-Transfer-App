//
// Created by David Exinor on 2024-04-24.
//

#include "MusicProfile.h"

// Constructor definition
MusicProfile::MusicProfile(string username, string password, Platform platform) {
    this->username = std::move(username);
    this->password = std::move(password);
    this->platform = platform;
}

// Getter definitions
string MusicProfile::getName() {return username;}
string MusicProfile::getPass() {return password;}
Platform MusicProfile::getPlatform() {return platform;}


