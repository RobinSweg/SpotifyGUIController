#pragma once
#include <string>

enum PlaybackOption{
    PLAY,
    PAUSE,
    SKIP,
    BACK,
};

class SpotifyAPI {
public:
    SpotifyAPI(const std::string& token);
    std::string fetchCurrentlyPlaying();
    std::string fetchTopSongs(); 
    int playMusic();
    void controlPlayback(PlaybackOption option);
private:
    std::string authToken;
};
