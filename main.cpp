#include <iostream>
#include "spotify_api.hpp"
#include "json.hpp"
#include <cstdlib> //for getenv
#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "config.hpp"
#include "shader_utils.hpp"

void initSDL(){
    SDL_Init(SDL_INIT_VIDEO);
    // Set to OpenGLES 3.0
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_Window* window = SDL_CreateWindow("Spotify GUI",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowDimensions::width, WindowDimensions::height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "GL Version: " << version << std::endl;

    GLuint shaderProgram = createShaderProgram("default.vert", "default.frag");
    glUseProgram(shaderProgram);

    GLuint VBO, VAO;
    // Save vertices to VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Panel::vertices), Panel::vertices, GL_STATIC_DRAW);    

    // Set mvp
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));

    // map to screen space instead of NDC so verticies are coordinate based
    glm::mat4 projection = glm::ortho(0.0f, (float) WindowDimensions::width, 0.0f, (float)WindowDimensions::height);
    glm::mat4 mvp = projection * model;


    // Set mvp uniform
    GLint mvpLocation = glGetUniformLocation(shaderProgram, "uMVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
    // Set colour to panel colour
    GLint colourLocation = glGetUniformLocation(shaderProgram, "uColour");
    glUniform4f(colourLocation, Theme::surfaceColour.r, Theme::surfaceColour.g, Theme::surfaceColour.b, 1.0f);  // light blue
    // set position
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN){
                std::cout << SDL_GetKeyName(event.key.keysym.sym) << std::endl;

            } 
        }
        
        //glClearColor(1.0f,1.0f,0.0f,1.0f);

        glClearColor(Theme::backgroundColour.r, Theme::backgroundColour.g, Theme::backgroundColour.b, Theme::backgroundColour.a);
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(Theme::backgroundColour.r, Theme::backgroundColour.g, Theme::backgroundColour.b, Theme::backgroundColour.a);
        glDrawArrays(GL_TRIANGLES, 0, 6);
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
