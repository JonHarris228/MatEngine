cmake_minimum_required(VERSION 3.24)
project(GameSDL)

set(CMAKE_CXX_STANDARD 23)

#add_library(MatEngine STATIC engine_lib/MatEngine.cpp)
#target_include_directories(MatEngine PUBLIC ${PROJECT_SOURCE_DIR}engine_lib/MatEngine.cpp)
#include_directories(GameSDL  ${PROJECT_SOURCE_DIR}/engine_lib/)

configure_file("${PROJECT_SOURCE_DIR}/include/source_path_in.h"
               "${PROJECT_SOURCE_DIR}/source_path.h")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(GameSDL test_card_game.cpp card.cpp)
target_link_libraries(GameSDL -lMatEngine -lmingw32 -lSDL2main -lSDL2 -lSDL2_image)