cmake_minimum_required(VERSION 3.0)
project(state C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable(state "${SOURCE}" src/game.c src/login.c src/menu.c src/map_choosing.c src/ai.c src/main.c)

include_directories("/usr/include/SDL2")
target_link_libraries(state m SDL2 SDL2_gfx SDL2_image SDL2_ttf SDL2_mixer)
