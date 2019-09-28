cmake_minimum_required(VERSION 3.7)
project(dreco-engine)

add_library(${PROJECT_NAME} STATIC
src/core/engine.cxx
src/core/sdl_event_manager.cxx
src/game_objects/game_base.cxx
src/game_objects/game_world.cxx
src/game_objects/game_object.cxx
src/game_objects/mesh_object.cxx
src/math/mat2x3.cxx
src/math/mat3x4.cxx
src/math/transform.cxx
src/math/vec2.cxx
src/renderer/opengles2_renderer.cxx
src/renderer/shader_gl_base.cxx
src/utils/file_utils.cxx)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(SDL2 REQUIRED)

target_link_libraries(${PROJECT_NAME}
    SDL2
    -lGL)

target_include_directories(${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/src/)