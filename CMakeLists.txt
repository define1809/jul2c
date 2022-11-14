cmake_minimum_required(VERSION 3.0)

project(jul2c VERSION 0.1 LANGUAGES C)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

file(GLOB SOURCES sources/*.c)

add_executable(jul2c ${SOURCES})

