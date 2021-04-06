cmake_minimum_required(VERSION 3.6)

add_subdirectory(bmp)
add_subdirectory(color)

project(Bmp24ToRgb565)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} bmp color)
include_directories(bmp color .)
