cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

add_library(shared SHARED shared.cpp)

add_executable(${ProjectId} main.cpp)
set_target_properties(${ProjectId} PROPERTIES INSTALL_RPATH $ORIGIN/../lib)
target_link_libraries(${ProjectId} ${CMAKE_DL_LIBS})

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)

INSTALL(TARGETS ${ProjectId} shared)