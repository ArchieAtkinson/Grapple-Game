cmake_minimum_required(VERSION 3.7...3.21)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Config
project(Grapple VERSION 1.0.0 LANGUAGES C CXX ASM)
configure_file(${CMAKE_SOURCE_DIR}/configuration/root_dir.c.in ${CMAKE_SOURCE_DIR}/src/root_dir.c)

# Source
# It is recommanded to manually add source files vs GOB
set(SOURCES 
src/main.c
src/objects.c
src/player.c
src/common.c
src/background.c
src/root_dir.c
)
set(HEADERS 
inc/objects.h
inc/player.h
inc/common.h
inc/background.h
inc/root_dir.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Libraries
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Options
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-DDEBUG>)