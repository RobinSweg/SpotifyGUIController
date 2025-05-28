#include <iostream>
#include "spotify_api.hpp"
#include "json.hpp"
#include <cstdlib> //for getenv
#include <SDL2/SDL.h>
#include <GLES2/gl2.h>


void initSDL(){
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Spotify GUI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 320,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN){
                std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;

            } 
        }

        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}

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

    initSDL();

    return 0;
}
