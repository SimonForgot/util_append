cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(module_name deformerDetector)
set(module_backend_name ${module_name}_backend)
set(module_loader_name ${module_name}_loader)

project(${module_name}_proj LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Maya REQUIRED)
find_package(SWIG REQUIRED)

include(${SWIG_USE_FILE})

add_library(${module_backend_name} SHARED main.cpp)
target_link_libraries(${module_backend_name} PRIVATE Maya::Maya)
set_target_properties(${module_backend_name} PROPERTIES PREFIX "") 

add_library(${module_loader_name} STATIC loader.cpp)
target_link_libraries(${module_loader_name} PRIVATE ${CMAKE_DL_LIBS})
set_target_properties(${module_loader_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)

find_package(Python COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
set_source_files_properties(swig.i PROPERTIES CPLUSPLUS ON
    SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON
    SWIG_FLAGS "-keyword")

swig_add_library(${module_name} TYPE MODULE LANGUAGE python SOURCES swig.i)
swig_link_libraries(${module_name} ${module_loader_name} $<$<PLATFORM_ID:Windows>:${Python_LIBRARIES}>)
set_target_properties(${module_name} PROPERTIES 
    PREFIX "" 
    INSTALL_RPATH $ORIGIN)

# install
INSTALL(TARGETS ${module_name} ${module_backend_name} DESTINATION ${MAYA_VERSION})
