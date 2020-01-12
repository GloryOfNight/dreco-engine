cmake_minimum_required(VERSION 3.7)
project(dreco-engine)

add_library(${PROJECT_NAME} SHARED
src/core/engine.cxx
src/core/sdl_event_manager.cxx
src/core/resource_manager.cxx
src/core/audio_manager.cxx
src/resources/resource.cxx
src/resources/audio.cxx
src/resources/music.cxx
src/resources/texture.cxx
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
src/utils/file_utils.cxx
src/utils/math_utils.cxx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")

set_target_properties(${PROJECT_NAME} PROPERTIES ENABLE_EXPORTS TRUE)

if(ANDROID)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/android/SDL2/src/main/SDL2/SDL2/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/android/SDL2/src/main/SDL2/SDL2_image)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/android/SDL2/src/main/SDL2/SDL2_mixer)
set(ANDROID_SDL_DIR "")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
set(ANDROID_SDL_DIR ${CMAKE_SOURCE_DIR}/android/SDL2/build/intermediates/ndkBuild/debug/obj/local/${CMAKE_ANDROID_ARCH_ABI})
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
set(ANDROID_SDL_DIR ${CMAKE_SOURCE_DIR}/android/SDL2/build/intermediates/ndkBuild/release/obj/local/${CMAKE_ANDROID_ARCH_ABI})
endif()

set(ANDROID_GLES_DIR "")
if (${CMAKE_ANDROID_ARCH_ABI} MATCHES "arm64-v8a")
set(ANDROID_GLES_DIR ${CMAKE_ANDROID_NDK}/platforms/android-29/arch-arm64/usr/lib/)
elseif (${CMAKE_ANDROID_ARCH_ABI} MATCHES "armeabi-v7a")
set(ANDROID_GLES_DIR ${CMAKE_ANDROID_NDK}/platforms/android-29/arch-arm/usr/lib/)
elseif (${CMAKE_ANDROID_ARCH_ABI} MATCHES "x86")
set(ANDROID_GLES_DIR ${CMAKE_ANDROID_NDK}/platforms/android-29/arch-x86/usr/lib/)
elseif (${CMAKE_ANDROID_ARCH_ABI} MATCHES "x86_64")
set(ANDROID_GLES_DIR ${CMAKE_ANDROID_NDK}/platforms/android-29/arch-x86_64/usr/lib64/)
endif()

target_link_libraries(${PROJECT_NAME}
    ${ANDROID_SDL_DIR}/libSDL2.so
    ${ANDROID_SDL_DIR}/libSDL2_image.so
    ${ANDROID_SDL_DIR}/libSDL2_mixer.so
    ${ANDROID_GLES_DIR}/libGLESv2.so)
elseif(UNIX)
target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2_image
    SDL2_mixer
    GL)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/src/)