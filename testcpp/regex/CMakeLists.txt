cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_executable(${ProjectId} main.cpp)

add_library(new SHARED regex_new_ABI.cpp)
target_compile_definitions(new PRIVATE _GLIBCXX_USE_CXX11_ABI=1)

add_library(old SHARED regex_old_ABI.cpp)
target_compile_definitions(old PRIVATE _GLIBCXX_USE_CXX11_ABI=0)

target_link_libraries(${ProjectId} PRIVATE new old)
target_compile_definitions(${ProjectId} PRIVATE _GLIBCXX_USE_CXX11_ABI=1)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)

INSTALL(TARGETS ${ProjectId})