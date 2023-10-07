cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_executable(${ProjectId} main.cpp)
add_library(A SHARED A.cpp)
add_library(B SHARED B.cpp)
target_compile_definitions(A PRIVATE _GLIBCXX_USE_CXX11_ABI=1)
#target_link_libraries(B A)

target_link_libraries(${ProjectId} B A)
target_compile_definitions(${ProjectId} PRIVATE _GLIBCXX_USE_CXX11_ABI=0)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)

INSTALL(TARGETS ${ProjectId})