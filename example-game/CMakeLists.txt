cmake_minimum_required(VERSION 3.7)
project(example-game)

set (SOURCE_LIST 
src/game_main.cxx
src/game_instance.cxx
src/world.cxx
src/game/game_board.cxx
src/game/gem.cxx
src/game/board_cell.cxx
src/game/gem_fall_component.cxx)

if (ANDROID) 
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST})
elseif(UNIX)
add_executable(${PROJECT_NAME} ${SOURCE_LIST})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

target_link_libraries(${PROJECT_NAME} dreco-engine)

if(UNIX) 
file(COPY res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
elseif (ANDROID)
file(COPY res/ DESTINATION ${CMAKE_HOME_DIRECTORY/android/app/src/main/assets)
endif()