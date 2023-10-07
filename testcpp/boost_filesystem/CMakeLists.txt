cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS filesystem)

add_library(test_lib SHARED test.cpp)
target_link_libraries(test_lib PRIVATE Boost::filesystem)

add_executable(${ProjectId} main.cpp)
target_link_libraries(${ProjectId} PRIVATE test_lib)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)
  
install(TARGETS ${ProjectId}) #DIRECTORIES ${Boost_LIBRARY_DIRS} 