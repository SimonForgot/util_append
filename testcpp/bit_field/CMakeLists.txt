cmake_minimum_required(VERSION 3.23)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_executable(${ProjectId} main.cpp)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)

set_target_properties(${ProjectId} PROPERTIES
  PUBLIC_HEADER "")
  
install(TARGETS ${ProjectId})
