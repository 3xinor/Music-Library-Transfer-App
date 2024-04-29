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

constexpr int CODE_VERIFIER_LENGTH = 128;
const string clientSecret = "CLIENTSECRET";
const string clientID = "f4cbe8b1857d4f878aaf54102f9188d1";
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
        string postData = "grant_type=" + requestData.grant_type + "&scope=playlist-modify-public";
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

// access spotify api endpoint and return the response
string songQuery(string token, Song song) {
    // construct the search query URL
    string searchURL = "https://api.spotify.com/v1/search?q=";
    searchURL += curl_easy_escape(nullptr, song.getName().c_str(), song.getName().length());
    searchURL += "+artist:";
    for (const auto& artist : song.getArtists()) {
        searchURL += curl_easy_escape(nullptr, artist.c_str(), artist.length());
        searchURL += ",";
    }
    searchURL.pop_back(); // remove the last comma
    searchURL += "&type=track";

    // initialize libcurl
    CURL *curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize libcurl." << endl;
        return "";
    }

    // set the request URL
    curl_easy_setopt(curl, CURLOPT_URL, searchURL.c_str());
    string response;

    // set the Authorization header
    string authHeader = "Authorization: Bearer " + token;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, authHeader.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // set write callback function to receive response data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // make request to api endpoint
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Failed to perform HTTP request: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        return "";
    }

    // cleanup libcurl
    curl_easy_cleanup(curl);

    // return the response
    return response;
}

/*
 * Creates an empty spotify playlist
 * Args:
 *      playlistName -> the desired name of playlist
 *      NOTE : The created playlist must be set to public for program to interact with it
 * returns true if successful, false otherwise
 */
bool createSpotifyPlaylist(string playlistName, string user, string token) {
    string playlistURL = "https://api.spotify.com/v1/users/" + user + "/playlists";
    // initialize curl
    CURL* curl = curl_easy_init();
    if (curl) {
        // set curl options
        curl_easy_setopt(curl, CURLOPT_URL, playlistURL.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // set authorization and content type headers
        string authHeader = "Authorization: Bearer " + token;
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, authHeader.c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set request body (json payload) **** need to CONFIGURE the PAYLOAD
        string jsonPayload = "{\"name\":\"" + playlistName + "\",\"description\":\"A playlist created using the Music-Library-Transfer-App\",\"public\":true}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());

        // response data
        string response;

        // set the callback function to handle response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "cURL request to generate Playlist failed: " << curl_easy_strerror(res) << endl;
            // clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        } else {
            // clean up
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            cout << "Playlist created successfully!" << endl;
            cout << response << endl;
            return true;
        }
    } else {
        cerr << "Failed to initialize cURL!" << endl;
        return false;
    }
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
        playlists.push_back(accessHREF(token, href, name));
    }
    return playlists;
}

/*
 * Find a song from spotifies catalogue and return the href of the song.
 * Note: The first occurence of a track of album type single will be captured
 * The function returns true if the song was found and false otherwise.
 */
bool SpotifyMusicAPI::findSong(Song* song) {
    // use search api endpoint to find all relevant songs
    string response = songQuery(token, *song);
    string songURI;
    // convert response string into json
    json responseJson = json::parse(response);

    // search response for track uri
    if (responseJson["tracks"]["items"].is_array()) {
        // iterate through the "items" of array
        for (const auto& item : responseJson["tracks"]["items"]) {
            // find the href of first single
            if (item["album"]["album_type"] == "single") {
                songURI = item["album"]["id"];
                // store the uri in the pass by referenced song object
                song->setSpotifyURI(songURI);
                return true;
            }
        }
    }
    // iterated through entire response and did not find any items of album type : single
    return false;
}

bool SpotifyMusicAPI::uploadPlaylist(PlayList playlist) {
    // create a new playlist
    bool created = createSpotifyPlaylist("TESTER 1", username, token);
    if (created) {
        // upload playlist catalogue to cloud
    }

    return false;
}