cmake_minimum_required(VERSION 3.7)
project(example-game)

add_executable(${PROJECT_NAME} 
src/game_main.cxx)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME} dreco-engine)

file(COPY res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)