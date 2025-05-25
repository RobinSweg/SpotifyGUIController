#include "spotify_api.hpp"
#include <curl/curl.h>
#include <sstream>
#include <iostream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

SpotifyAPI::SpotifyAPI(const std::string& token) : authToken(token) {}

std::string SpotifyAPI::fetchCurrentlyPlaying() {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: Bearer " + authToken;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/player/currently-playing");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // Rewrite the callback to reponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

std::string SpotifyAPI::fetchTopSongs() {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: Bearer " + authToken;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/top/tracks?limit=50");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // Rewrite the callback to reponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

int SpotifyAPI:: playMusic() {
    CURL* curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: Bearer " + authToken;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/player/play");
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");  

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return 1;
}

void SpotifyAPI:: controlPlayback(PlaybackOption option){
    CURL* curl = curl_easy_init();

    if (curl) {
        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: Bearer " + authToken;
        headers = curl_slist_append(headers, authHeader.c_str());
        
        PlaybackOption play = PLAY;
        PlaybackOption pause = PAUSE;
        PlaybackOption skip = SKIP;
        if (option == play){
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/player/play");
 

        } else if (option == pause){
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/player/pause");

        } else if (option == skip){
            std::cout << "Skipping " << std::endl;
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.spotify.com/v1/me/player/next");
        }
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");  

        curl_easy_perform(curl); // this return text after request
        curl_easy_cleanup(curl);
    }
}