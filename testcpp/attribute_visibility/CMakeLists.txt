cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_library(${ProjectId}_lib SHARED test.cpp)
target_include_directories(${ProjectId}_lib PRIVATE ./)

add_executable(${ProjectId}_exe main.cpp)
target_link_libraries(${ProjectId}_exe PRIVATE ${ProjectId}_lib)
target_include_directories(${ProjectId}_exe PRIVATE ./)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}_exe>)

INSTALL(TARGETS ${ProjectId}_lib)
INSTALL(TARGETS ${ProjectId}_exe)