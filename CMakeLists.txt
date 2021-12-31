cmake_minimum_required(VERSION 3.7...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(Grapple)
enable_language( C CXX ASM )

configure_file(${CMAKE_SOURCE_DIR}/configuration/root_dir.c.in ${CMAKE_SOURCE_DIR}/src/root_dir.c)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} 
"src/main.c"
"src/objects.c"
"src/player.c"
"src/common.c"
"src/background.c"
"src/root_dir.c"
"inc/objects.h"
"inc/player.h"
"inc/common.h"
"inc/background.h"
"inc/root_dir.h"
) # It is recommanded to manually add source files.

target_include_directories(${PROJECT_NAME} PRIVATE inc)

add_subdirectory(external/raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_include_directories(${PROJECT_NAME} PRIVATE ./external/raylib/src/extras)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-DDEBUG>)