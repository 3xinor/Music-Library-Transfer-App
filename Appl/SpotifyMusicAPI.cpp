//
// Created by David Exinor on 2024-04-25.
//

#include <iostream>
#include <random>
#include <openssl/evp.h>
#include <curl/curl.h>
#include "SpotifyMusicAPI.h"

constexpr int CODE_VERIFIER_LENGTH = 128;
const string clientID = "f4cbe8b1857d4f878aaf54102f9188d1";
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
     * Authorization code with PKCE(Proof Key for Code Exchange) Flow
     * 1. code verifier
     * 2. code challenge(sha 256)
     * 3. request authorization
     * 4. request an access token
     * 5. return the access token to be used elsewhere
     */

    // code verifier and challenge generation
    string codeVerifier = generateCodeVerifier();
    string codeChallenge = base64urlEncode(sha256(codeVerifier));

    // Construct authorization endpoint GET request params
    string url = authURL;
    url += "?response_type=code";
    url += "&client_id=" + clientID;
    url += "&redirect_uri=" + redirectURL;
    url += "&code_challenge_method=S256";
    url += "&code_challenge=" + codeChallenge;

    // initialize libcurl
    /*
    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Error: Unable to initialize libcurl." << endl;
        return false;
    }

    // set the url for the GET request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // perform GET request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "Error: Failed to perform GET request: " << curl_easy_strerror(res) << endl;
        curl_easy_cleanup(curl);
        return false;
    }*/

    return true;
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