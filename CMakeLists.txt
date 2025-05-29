cmake_minimum_required(VERSION 3.10)
project(SpotifyGUI)

set(CMAKE_CXX_STANDARD 17)

add_executable(SpotifyGUI main.cpp spotify_api.cpp shader_utils.cpp)

# CURL
find_package(CURL REQUIRED)
target_include_directories(SpotifyGUI PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(SpotifyGUI PRIVATE ${CURL_LIBRARIES})

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(SpotifyGUI PRIVATE ${SDL2_LIBRARIES})

# OpenGLES
find_library(GLESv2_LIBRARY GLESv2)
target_link_libraries(SpotifyGUI PRIVATE ${GLESv2_LIBRARY})
