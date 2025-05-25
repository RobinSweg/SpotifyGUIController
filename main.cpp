#include <iostream>
#include "spotify_api.hpp"
#include "json.hpp"
#include <cstdlib> //for getenv

int main() {
    std::string token = std::getenv("ACCESSTOKEN");
    SpotifyAPI api(token);
    /*
    std::string response = api.fetchCurrentlyPlaying();
    if (!response.empty()) {
        auto json = nlohmann::json::parse(response);
        //std::cout << json;
        
        
        std::cout << "Now playing: " 
                  << json["item"]["name"] << " by " 
                  << json["item"]["artists"][0]["name"] 
                  << " released on: "
                  << json["item"]["album"]["release_date"]
                  << std::endl;
        
    } else {
        std::cout << "No response or nothing playing." << std::endl;
    }

    std::string tracks = api.fetchTopSongs();
    if (!tracks.empty()) {
        auto json = nlohmann::json::parse(tracks);
        for (int iSong = 0; iSong <50 ; iSong++)
        {
            std::cout << "Top Track [" << iSong << "]" << " "
            << json["items"][iSong]["name"] << std::endl;
        }
        
        
    } else {
        std::cout << "No response or nothing playing." << std::endl;

    }
    */
    PlaybackOption play = PLAY;
    PlaybackOption pause = PAUSE;
    //api.controlPlayback(pause);

    PlaybackOption skip = SKIP;
    api.controlPlayback(skip);


    
    std::cout << std::endl;
    return 0;
}
