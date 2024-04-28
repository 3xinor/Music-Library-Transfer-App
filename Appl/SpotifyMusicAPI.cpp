//
// Created by David Exinor on 2024-04-25.
//

#include <iostream>
#include <random>
#include <openssl/evp.h>
#include "httplib.h"
#include <curl/curl.h>
#include "SpotifyMusicAPI.h"

const string clientSecret = "794f812db68949d5b090ee89ea516e79";

constexpr int CODE_VERIFIER_LENGTH = 128;
const string clientID = "f4cbe8b1857d4f878aaf54102f9188d1";
const string tokenURL = "https://accounts.spotify.com/api/token";
const string redirectURL = "http://localhost:8888/callback";
const string authURL = "https://accounts.spotify.com/authorize";


SpotifyMusicAPI::SpotifyMusicAPI() : WebDomainAPI() {
    //TODO
    // do i need to do more? who knows?
}

/********* Spotify API specific functions *********/

/*
 * Generates and returns a PKCE compliant string
 */
string generateCodeVerifier() {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~";
    random_device rand;
    mt19937 gen(rand());
    uniform_int_distribution<int> dist(0, charset.size() - 1);

    string codeVerifier;
    for (int i = 0 ; i < CODE_VERIFIER_LENGTH ; ++i) {
        codeVerifier += charset[dist(gen)];
    }
    return codeVerifier;
}

/*
 * Hashes a string using SHA-256 algorithm
 */
string sha256(const string& input) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    md = EVP_sha256();
    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, input.c_str(), input.length());
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);
    EVP_MD_CTX_free(mdctx);

    string hashStr(reinterpret_cast<char*>(hash), hashLen);
    return hashStr;
}

/*
 * Calculate Base64URL-encoded string
 */
string base64urlEncode(const string& input) {
    string encoded;
    EVP_EncodeBlock(reinterpret_cast<unsigned char*>(&encoded[0]), reinterpret_cast<const unsigned char*>(&input[0]), input.size());
    size_t padding = input.size() % 3;
    if (padding > 0) {
        encoded.resize(encoded.size() - padding);
    }
    replace(encoded.begin(), encoded.end(),'+', '-');
    replace(encoded.begin(), encoded.end(),'/', '-');

    return encoded;
}

/*
 * Callback function to write repsonse data
 */
size_t writeCallback(char* ptr, size_t size, size_t nmemb, string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

/********* Overriding pure virtual functions to implement api specific methods used in application *********/

bool SpotifyMusicAPI::connectToCloud(std::string username, std::string password) {
    /*
     * Obtaining an access token using client credentials


    // base64 encode client ID and client secret
    string authorization = "Basic " + httplib::detail::base64_encode(clientID + ":" + clientSecret);

    // Create a POST request to the token URL with authorization header and grant type
    httplib::Client client("accounts.spotify.com", 443);
    httplib::Params params = {{"grant_type", "client_credentials"}};
    httplib::Headers headers = {{"Authorization", authorization}};
    auto response = client.Post(tokenURL, headers, params);

    // check if request was successful
    if (response && response->status == 200) {
        // Parse the JSON to extract the access token
        string access_token = response->body;
        cout << "Access Token: " << access_token << endl;
        return true;
    }
    cout << "Error: Failed to obtain access token. Response Status: " << response->status << endl << endl;
    cout << response->body << endl;
    return false;*/

    CURL *curl;
    CURLcode res;
    string response;


    // initialize libcurl
    curl = curl_easy_init();
    return false;
}

vector<string> SpotifyMusicAPI::findPlayLists() {
    //TODO
    vector<string> temp = {};
    return temp;
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