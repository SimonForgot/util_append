cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(BipedCOMValueScale LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../")

find_package(MAXSDK REQUIRED)

add_library(BipedCOMValueScale SHARED BipedCOMValueScale.cpp)
target_include_directories(BipedCOMValueScale PRIVATE ${MAXSDK_INCLUDE_DIR} ${CMAKE_SOURCE_DIR})
target_link_libraries(BipedCOMValueScale ${MAXSDK_LIBS})
target_compile_definitions(BipedCOMValueScale PRIVATE NOMINMAX UNICODE _UNICODE)
set_target_properties(BipedCOMValueScale PROPERTIES SUFFIX ".dlx")

INSTALL(TARGETS BipedCOMValueScale
RUNTIME DESTINATION . 
LIBRARY DESTINATION .
ARCHIVE DESTINATION .
)