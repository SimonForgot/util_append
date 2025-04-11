cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MyPlugIn LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../")

find_package(MAXSDK REQUIRED)

add_library(MyPlugIn SHARED MyPlugIn.cpp HelloUtil.cpp)
target_include_directories(MyPlugIn PRIVATE ${MAXSDK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR})
target_link_libraries(MyPlugIn ${MAXSDK_core_LIBRARY} ${MAXSDK_maxutil_LIBRARY} ${MAXSDK_paramblk2_LIBRARY})
target_compile_definitions(MyPlugIn PRIVATE NOMINMAX UNICODE _UNICODE)
set_target_properties(MyPlugIn PROPERTIES SUFFIX ".dlu")

INSTALL(TARGETS MyPlugIn)