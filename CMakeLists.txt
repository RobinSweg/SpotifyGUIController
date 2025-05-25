cmake_minimum_required(VERSION 3.10)
project(SpotifyGUI)

set(CMAKE_CXX_STANDARD 17)

add_executable(SpotifyGUI main.cpp spotify_api.cpp)

find_package(CURL REQUIRED)
target_include_directories(SpotifyGUI PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(SpotifyGUI PRIVATE ${CURL_LIBRARIES})
