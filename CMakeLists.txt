cmake_minimum_required(VERSION 3.7)
project(dreco-project)


if (ANDROID)
# copy java files from SDL2 sources to app
file(COPY ${PROJECT_SOURCE_DIR}/android/SDL2/src/main/SDL2/SDL2/android-project/app/src/main/java/org/libsdl DESTINATION ${PROJECT_SOURCE_DIR}/android/app/src/main/java/org/libsdl)
endif()

add_subdirectory(dreco-engine)
add_subdirectory(example-game) 
