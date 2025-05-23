cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MyPlugIn LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../")

find_package(MAXSDK REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core GUI REQUIRED)

add_library(MyPlugIn SHARED MyPlugIn.cpp HelloUtil.cpp)
target_include_directories(MyPlugIn PRIVATE ${MAXSDK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR})
target_link_libraries(MyPlugIn ${MAXSDK_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui)
target_compile_definitions(MyPlugIn PRIVATE NOMINMAX UNICODE _UNICODE)
set_target_properties(MyPlugIn PROPERTIES SUFFIX ".dlu")

INSTALL(TARGETS MyPlugIn)