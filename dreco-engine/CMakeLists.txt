cmake_minimum_required(VERSION 3.7)
project(dreco-engine)

add_library(${PROJECT_NAME} STATIC
src/core/engine.cxx
src/core/sdl_event_manager.cxx)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME}
    SDL2
    -lGL)