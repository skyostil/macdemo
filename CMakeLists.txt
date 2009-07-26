project(Monoxide)
cmake_minimum_required(VERSION 2.6)

set(SOURCES
    main.c
    monoxide.c
    monoxide_sdl.c
)

find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDLIMAGE_INCLUDE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

link_libraries(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
)

add_executable(
    monoxide
    WIN32
    MACOSX_BUNDLE
    ${SOURCES}
)

# ctags
if (NOT APPLE AND NOT WIN32)
    add_custom_command (TARGET monoxide POST_BUILD
                        COMMAND ctags --c++-kinds=+p --fields=+iaS --extra=+q 
                                -R .
                        COMMENT "Creating tags" VERBATIM)
endif (NOT APPLE AND NOT WIN32)
