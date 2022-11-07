cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(TBB REQUIRED)

add_executable(${ProjectId} main.cpp)
target_link_libraries(${ProjectId} Boost::filesystem TBB::tbb)
set_target_properties(${ProjectId} PROPERTIES INSTALL_RPATH $ORIGIN/../lib)

add_custom_target(run COMMAND $<TARGET_FILE:${ProjectId}>)
  
install(TARGETS ${ProjectId} RUNTIME_DEPENDENCIES) #DIRECTORIES ${Boost_LIBRARY_DIRS} 
