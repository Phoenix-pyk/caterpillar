cmake_minimum_required(VERSION 3.30)
project(snake)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_executable(snake main.cpp)
target_link_libraries(snake PRIVATE SDL2::SDL2)

add_executable(sdltest sdltest.cpp)
target_link_libraries(sdltest PRIVATE SDL2::SDL2)

add_executable(basic_game_loop basic_game_loop.cpp)
target_link_libraries(basic_game_loop PRIVATE SDL2::SDL2)
