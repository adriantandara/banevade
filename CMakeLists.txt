cmake_minimum_required(VERSION 3.29)
project(BanEvade)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "D:/Games/Modpack samp/Modpack Winter Medium PC - HeroCaT")

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp" "*.h")
add_library(BanEvade SHARED ${SOURCES})

add_custom_command(TARGET BanEvade POST_BUILD COMMAND ${CMAKE_COMMAND} -E rename "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/BanEvade.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/banevade.asi")