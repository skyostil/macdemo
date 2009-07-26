project(MacDemo)
cmake_minimum_required(VERSION 2.6)

set(SOURCES
    monoxide/monoxide.c
    monoxide/monoxide_blit.c
    engine/Engine.cpp
    engine/Audio.cpp
    engine/Mixer.cpp
    engine/SdlVideo.cpp
    engine/SdlAudio.cpp
    FixedPointMath.cpp
    FixedPointMatrix.cpp
    FixedPointVector.cpp
    ModPlayer.cpp
    Main.cpp
    demo.c
)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})
include_directories(engine)
include_directories(monoxide)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
add_definitions(-DHAVE_STDINT_H)
add_definitions(-DUSE_SDL)

link_libraries(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
)

add_executable(
    macdemo
    WIN32
    MACOSX_BUNDLE
    ${SOURCES}
)

# ctags
if (NOT APPLE AND NOT WIN32)
    add_custom_command (TARGET macdemo POST_BUILD
                        COMMAND ctags --c++-kinds=+p --fields=+iaS --extra=+q 
                                -R .
                        COMMENT "Creating tags" VERBATIM)
endif (NOT APPLE AND NOT WIN32)
