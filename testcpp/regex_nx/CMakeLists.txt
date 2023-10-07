cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

find_package(Boost COMPONENTS filesystem regex)

add_library(old_ABI SHARED regex_old_ABI.cpp)
target_compile_definitions(old_ABI PRIVATE _GLIBCXX_USE_CXX11_ABI=0)

file(GLOB sources CONFIGURE_DEPENDS of3d_license/*.cpp of3d_license/*.h)
add_library(of3d_license SHARED ${sources})
target_compile_definitions(of3d_license PRIVATE _GLIBCXX_USE_CXX11_ABI=1)
target_link_libraries(of3d_license Boost::filesystem Boost::regex)

add_executable(${ProjectId} main.cpp)
target_link_libraries(${ProjectId} old_ABI of3d_license)
file(GLOB of3d_license_headers CONFIGURE_DEPENDS of3d_license)
target_include_directories(${ProjectId} PRIVATE ${of3d_license_headers})

#-static-libstdc++

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)

INSTALL(TARGETS ${ProjectId})