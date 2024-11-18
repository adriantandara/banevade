cmake_minimum_required(VERSION 3.29)
project(BanEvade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "D:/Games/Modpack samp/Modpack Winter Medium PC - HeroCaT")

add_subdirectory(external/samp-api)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/external/samp-api/include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_library(BanEvade SHARED ${SOURCES})

target_link_libraries(BanEvade PRIVATE sampapi)
target_include_directories(BanEvade PRIVATE external/samp-api/include)

add_custom_command(
        TARGET BanEvade
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BanEvade.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/banevade.asi"
)
