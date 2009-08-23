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
    ModPlayer.cpp
    Main.cpp
    Font.cpp
    Demo.cpp
)

find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
include_directories(engine)
include_directories(monoxide)
include_directories(.)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
add_definitions(-DUSE_SDL)

link_libraries(
    ${SDL_LIBRARY}
)

if (WIN32)
    link_libraries(${SDLMAIN_LIBRARY})
    if (MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MT")
    endif (MSVC)
endif (WIN32)

if (NOT APPLE AND NOT WIN32)
    add_definitions(-DHAVE_STDINT_H)
    add_custom_command (TARGET macdemo POST_BUILD
                        COMMAND ctags --c++-kinds=+p --fields=+iaS --extra=+q 
                                -R .
                        COMMENT "Creating tags" VERBATIM)
endif (NOT APPLE AND NOT WIN32)

add_executable(
    three_and_a_half_inches_is_enough
    WIN32
    MACOSX_BUNDLE
    ${SOURCES}
)
