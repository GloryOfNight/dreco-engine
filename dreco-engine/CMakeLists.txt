cmake_minimum_required(VERSION 3.7)
project(dreco-engine)

add_library(${PROJECT_NAME} SHARED
src/core/engine.cxx
src/core/sdl_event_manager.cxx
src/game_objects/camera_base.cxx
src/game_objects/game_base.cxx
src/game_objects/game_world.cxx
src/game_objects/game_object.cxx
src/game_objects/mesh_object.cxx
src/math/mat2x3.cxx
src/math/transform.cxx
src/math/vec2.cxx
src/math/int_vec2.cxx
src/math/vec3.cxx
src/renderer/opengles2_renderer.cxx
src/renderer/vertex_properties.cxx
src/renderer/shader_gl_base.cxx
src/renderer/texture.cxx
src/utils/file_utils.cxx
src/utils/math_utils.cxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)

if(${Android})
target_include_directories(${PROJECT_NAME} PUBLIC /home/siarheidziki/GitHub/SDL2/SDL2-2.0.10/include)
target_include_directories(${PROJECT_NAME} PUBLIC /home/siarheidziki/GitHub/SDL2/SDL2_image-2.0.5)

set(ANDROID_SDL_DIR ${CMAKE_SOURCE_DIR}/android/SDL2/build/intermediates/ndkBuild/debug/obj/local/armeabi-v7a)

target_link_libraries(${PROJECT_NAME}
    ${ANDROID_SDL_DIR}/libSDL2.so
    ${ANDROID_SDL_DIR}/libSDL2_image.so
    /home/siarheidziki/Android/sdk/ndk/20.1.5948944/platforms/android-29/arch-arm/usr/lib/libGLESv2.so)
else()
target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2_image
    GL)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/src/)