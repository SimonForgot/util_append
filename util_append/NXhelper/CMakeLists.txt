cmake_minimum_required(VERSION 3.15)
project(NXhelper)

file(GLOB NXHELP_FILES NX*)
add_library(NXhelper SHARED ${NXHELP_FILES})
find_package(NXRenderer REQUIRED)
target_link_libraries(NXhelper
    ${NXRENDERER_LIBRARY}
    ${ARNOLD_ROOT}/bin/libai.so)
target_include_directories(NXhelper PUBLIC
    ${NXRENDERER_INCLUDE_DIRS}
    ${ARNOLD_ROOT}/include)

file(GLOB NXHELP_HEADERS *.h)
set_target_properties(NXhelper PROPERTIES PUBLIC_HEADER ${NXHELP_HEADERS})
install(TARGETS NXhelper)

# main for test
add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE NXhelper)
add_custom_target(run COMMAND $<TARGET_FILE:demo>)
