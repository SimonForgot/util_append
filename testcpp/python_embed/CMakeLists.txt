cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(demo)

# Find python and Boost - both are required dependencies
find_package(Python3 COMPONENTS Development REQUIRED)
# Without this, any build libraries automatically have names "lib{x}.so"
set(CMAKE_SHARED_MODULE_PREFIX "")
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} Python3::Python)

add_custom_target(run COMMAND $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

INSTALL(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION .)