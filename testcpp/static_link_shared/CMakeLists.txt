cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_executable(${ProjectId} main.cpp)
target_link_libraries(${ProjectId} /home/zhangxinlong/repo/test/testcpp/static_link_shared/install/libstatic_lib.a
/home/zhangxinlong/repo/test/testcpp/static_link_shared/install/libshared_lib.so)