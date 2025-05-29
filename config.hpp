#pragma once
#include <glm/glm.hpp>

namespace Theme {
    const glm::vec4 backgroundColour = glm::vec4(18.0f / 255.0f, 18.0f / 255.0f, 18.0f / 255.0 ,1.0f);
    const glm::vec4 surfaceColour = glm::vec4(33.0f / 255.0f, 33.0f / 255.0f, 33.0f / 255.0f, 1.0f);
    const glm::vec3 borderColour = glm::vec4(83.0f / 255.0f, 83.0f / 255.0f, 83.0f / 255.0f, 1.0f);  
    const glm::vec4 greenColour = glm::vec4(29.0f / 255.0f, 185.0f / 255.0f, 84.0f / 255.0f, 1.0f);
    const glm::vec4 textColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

namespace WindowDimensions {
    const int width = 320;
    const int height = 240;

}

namespace Panel{
    float x = 40.0f;   
    float y = 0.0f;
    float width = 240.0f;
    float height = 240.0f;

    float vertices[] = {
        // tri 1
        x, y + height,
        x, y,       
        x+width, y+height,
        // tri 2
        x+width, y+height,
        x,y,
        x+width, y
    };
}