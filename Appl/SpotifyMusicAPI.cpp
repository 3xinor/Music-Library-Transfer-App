//
// Created by David Exinor on 2024-04-25.
//

#include <iostream>
#include <random>
#include <tuple>
#include <openssl/evp.h>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "SpotifyMusicAPI.h"

using json = nlohmann::json;
// Define a type alias for the tuple representing a playlist
using PlaylistTuple = std::tuple<std::string, std::string>;

const string clientSecret = "CLIENTSECRET";

constexpr int CODE_VERIFIER_LENGTH = 128;
const string clientID = "CLIENTID";
const string tokenURL = "https://accounts.spotify.com/api/token";
const string redirectURL = "http://localhost:8888/callback";


SpotifyMusicAPI::SpotifyMusicAPI(string user) : WebDomainAPI() {
    this->username = user;
}

/********* Spotify API specific functions *********/

// Encode given string for client id/secret encoding
string base64Encode(const string &input) {
    const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

    std::string encoded;
    int bits = 0;
    int bit_count = 0;

    for (unsigned char c : input) {
        bits = (bits << 8) + c;
        bit_count += 8;
        while (bit_count >= 6) {
            encoded.push_back(base64_chars[(bits >> (bit_count - 6)) & 0x3F]);
            bit_count -= 6;
        }
    }

    if (bit_count > 0) {
        bits <<= (6 - bit_count);
        encoded.push_back(base64_chars[bits & 0x3F]);
    }

    while (encoded.size() % 4) {
        encoded.push_back('=');
    }

    return encoded;
}

// callback function to write response data
size_t writeCallback(void *contents, size_t size, size_t nmemb, string *response) {
    response->append((char *)contents, size * nmemb);
    return size *nmemb;
}

// function to make POST request
string make_post_request(const RequestData &requestData) {
    CURL *curl;
    CURLcode res;
    string response;

    // initialize libcurl
    curl = curl_easy_init();
    if (curl) {
        // set the url
        curl_easy_setopt(curl, CURLOPT_URL, requestData.url.c_str());

        // set the Authorization header
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: " + requestData.authorization).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set the POST data
        string postData = "grant_type=" + requestData.grant_type;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // set the write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        // check for errors
        if (res != CURLE_OK) {
            cerr << "Error: Failed to perform POST request: " << curl_easy_strerror(res) << endl;
            return "";
        }
    } else {
        cerr << "Error: Failed to initialize libcurl." << endl;
        return "";
    }
    return response;
}

// aquires the playlist href links for the user
vector<PlaylistTuple> acquirePlaylistHREFs(string username, string token){
    cout << "Consolidating Playlist HREFs" << endl;
    // return list containing all hrefs for each playlist
    vector<PlaylistTuple> playlists = {};

    // format playlists endpoint for given user
    string playlistsURL = "https://api.spotify.com/v1/users/{user_id}/playlists";
    size_t pos = playlistsURL.find("{user_id}");
    if (pos != string::npos) {
        playlistsURL.replace(pos, string("{user_id}").length(), username);
    }

    // initialize llibcurl
    CURL *curl = curl_easy_init();
    if (curl) {
        // set the URL
        curl_easy_setopt(curl, CURLOPT_URL, playlistsURL.c_str());

        // set the Authorization header
        string authHeader = "Authorization: Bearer " + token;
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set the write callback function
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the request
        CURLcode res = curl_easy_perform(curl);

        // check for errors
        if (res != CURLE_OK) {
            cerr << "Error: Failed to perform the GET request: " << curl_easy_strerror(res) << endl;

        } else {
            // parsing and storing each playlists href url
            json response_json = json::parse(response);

            // check if the "items" array exists in the repsonse
            if (response_json.find("items") != response_json.end() && response_json["items"].is_array()) {
                // iterate through the "items" array
                for (const auto& item : response_json["items"]) {
                    // Check if the "tracks" object exists for the current object
                    if (item.find("tracks") != item.end() && item["tracks"].is_object()) {
                        // get and store the "href" and name for each playlist
                        string href = item["tracks"]["href"];
                        string name = item["name"];
                        playlists.push_back(make_tuple(name, href));
                    }
                }
            }
        }

        // cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        cerr << "Error: Failed to initialize libcurl." << endl;
    }

    return playlists;
}

// access href endpoint
PlayList accessHREF(string token, string href, string playlistName) {
    // create a new playlist object
    cout << "Accessing HREF for the Playlist: " << playlistName << endl;
    PlayList newPlaylist = {playlistName};
    // initialize llibcurl
    CURL *curl = curl_easy_init();
    if (curl) {
        // set the URL
        curl_easy_setopt(curl, CURLOPT_URL, href.c_str());

        // set the Authorization header
        string authHeader = "Authorization: Bearer " + token;
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set the write callback function
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the request
        CURLcode res = curl_easy_perform(curl);

        // check for errors
        if (res != CURLE_OK) {
            cerr << "Error: Failed to perform the GET request: " << curl_easy_strerror(res) << endl;

        } else {
            // parsing href response json for all tracks and related info
            json responseJson = json::parse(response);

            // check if the "items" array exists in response
            if (responseJson.find("items") != responseJson.end() && responseJson["items"].is_array()) {
                // iterate through the "items" array
                for (const auto& item : responseJson["items"]) {
                    // find all relevant song info
                    string songName = item["track"]["name"];
                    string album = item["track"]["album"]["name"];
                    string release = item["track"]["album"]["release_date"];
                    double timeLength = item["track"]["duration_ms"];
                    // append all artists
                    vector<string> artists;
                    for (const auto& artist : item["track"]["artists"]) {
                        artists.push_back(artist["name"]);
                    }
                    cout << "\t\tCreating a Song object for: " << songName << endl;
                    // create a Song object and add it to the new Playlist
                    Song newSong = {songName, artists, album, timeLength, release};
                    newPlaylist.addSong(newSong);
                }
            }
        }

        // cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    } else {
        cerr << "Error: Failed to initialize libcurl." << endl;
    }
    return newPlaylist;
}

/********* Overriding pure virtual functions to implement api specific methods used in application *********/

bool SpotifyMusicAPI::connectToCloud() {
    /*
     *  Obtaining an access token using client credentials
     */

    cout << "Connecting to Spotify API to generate access token" << endl;
    // bas64 encode client ID and client secret for authorization header
    string authorization = "Basic ";
    authorization += base64Encode(clientID + ":" + clientSecret);

    // create request data
    RequestData requestData;
    requestData.url = tokenURL;
    requestData.authorization = authorization;
    requestData.grant_type = "client_credentials";

    // make the POST request
    string response = make_post_request(requestData);

    // check if the request was successful
    if (!response.empty()) {
        // extract token from spotify authorization response
        json response_json = json::parse(response);
        string access_token = response_json["access_token"];
        token = access_token;
        cout << "Access Token: " << token << endl;
        return true;
        cout << "Connection to API completed" << endl << endl;
    }
    return false;
}

vector<PlayList> SpotifyMusicAPI::findPlayLists() {
    cout << "Searching for all user playlists" << endl;
    vector<PlayList> playlists;
    // find all playlists refs for the user
    vector<PlaylistTuple> playlistTuples = acquirePlaylistHREFs(username, token);
    for (const auto& playlist : playlistTuples) {
        string name = get<0>(playlist);
        string href = get<1>(playlist);
        // save playlist info after accessing HREF
        accessHREF(token, href, name);
    }

    return playlists;
}

bool SpotifyMusicAPI::getPlayList(std::string playList) {
    //TODO
    return false;
}

bool SpotifyMusicAPI::findSong(Song song) {
    //TODO
    return false;
}

bool SpotifyMusicAPI::uploadPlaylist(PlayList playlist) {
    //TODO
    return false;
}