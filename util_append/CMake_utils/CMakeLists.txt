cmake_minimum_required(VERSION 3.18)

#放在project之前，不要用CMAKE_CXX_FLAGS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#use folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)


#find_package 生成的伪对象(imported target)都按照“包名::组件名”的格式命名。
#你可以在 find_package 中通过 COMPONENTS 选项，后面跟随一个列表表示需要用的组件。
#CONFIG表示只接受config模式不接受Findxxx模式
find_package(TBB CONFIG COMPONENTS tbb tbbmalloc REQUIRED)
target_link_libraries(main PUBLIC TBB::tbb TBB::tbbmalloc)



#XXX_DIR设置之后，find_package就会去该处找XXXConfig.cmake
#如果没有设置，则系统会在cmake的默认位置找自带的config文件，并在找到库之后将XXX_DIR设置为该地址
set(Qt5_DIR /home/zhangxinlong/mnt/apps/gaffer-dev/gafferDependencies-2.2.0-Python2-linux/lib/cmake/Qt5)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets Gui)
target_compile_options(main PUBLIC WITH_QT)#未来就可以在main里按照条件做实现

#判断是否找到TARGET伪对象的另一种方式
if(TARGET QT5::Gui) 

#启用 CONFIGURE_DEPENDS 选项，当添加新文件时，自动更新变量
aux_source_directory(. sources)
#file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
#file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.cpp *.h)  可能把build下的cpp也包进来


#让动态库可以link静态库
add_library(my_staticlib STATIC xxx.cpp)
set_target_properties(my_staticlib PROPERTIES POSITION_INDEPENDENT_CODE ON)
#然后其他动态库就可以link它了


#IMPORT的target（称IMPORT target为伪对象，没有实体），可用于编写FindXXX.cmake
if (NOT TARGET Maya::Maya)
    add_library(Maya::Maya UNKNOWN IMPORTED)
    set_target_properties(Maya::Maya PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "${MAYA_COMPILE_DEFINITIONS}"
        INTERFACE_INCLUDE_DIRECTORIES "${MAYA_INCLUDE_DIR}"
        IMPORTED_LOCATION "${MAYA_LIBRARY}")
    
    if (APPLE AND ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND MAYA_VERSION LESS 2018)
        # Clang and Maya 2016 and older needs to use libstdc++
        set_target_properties(Maya::Maya PROPERTIES
            INTERFACE_COMPILE_OPTIONS "-std=c++0x;-stdlib=libstdc++")
    endif ()
endif()



message(AUTHOR_WARNING "only author can see,give -Wno-dev to cmake can ignore this")
message(SEND_ERROR)#error and continue run
message(FATAL_ERROR)#error and break 

#设置cache变量的默认值；用户-D的值会覆盖它。
option(XXX "Bool option" ON)
#下面这种方式设置默认值可以不进cache
if(NOT DEFINED XXX)
    set(XXX ON)
endif()

#if (DEFINED MYVAR) 可以判断是否存在 MYVAR 这个局部变量或缓存变量

#if(变量)不用加${}

message("$ENV{PATH}")
message("$CACHE{CMAKE_BUILD_TYPE}")
#当${}找不到普通变量时，就会去找cache变量
message("${CMAKE_BUILD_TYPE}")



#带PROJECT的表示[最近一次调用]project的
#${PROJECT_NAME} 最近一次project名
#${CMAKE_PROJECT_NAME} 顶层project名
#PROJECT_SOURCE_DIR 表示最近一次调用 project 的 CMakeLists.txt 所在的源码目录。

#不带CURRENT的CMAKE_前缀 是表示顶层的，加了CURRENT的才是当前的
#CMAKE_CURRENT_SOURCE_DIR 表示当前 CMakeLists.txt 所在的源码目录。
#CMAKE_SOURCE_DIR 表示最为外层 CMakeLists.txt 的源码根目录。
#利用 PROJECT_SOURCE_DIR 可以实现从子模块里直接获得项目最外层目录的路径

#PROJECT_IS_TOP_LEVEL：BOOL类型，表示当前项目是否是（最顶层的）根项目
#PROJECT_NAME：当前项目名
#CMAKE_PROJECT_NAME：根项目的项目名

#所以使用裸的CMAKE_不是一个好习惯
#使用project来管理比较清晰，相当于是一个新的project，方便复用
if(WIN32)
    add_definitions(-DNOMINMAX -D_USE_MATH_DEFINES)
endif()

#相比于动态库，静态库没有跨平台的困扰

#add_library 无参数时，是静态库还是动态库?
会根据 BUILD_SHARED_LIBS 这个变量的值决定是动态库还是静态库。
ON 则相当于 SHARED，OFF 则相当于 STATIC。
如果未指定 BUILD_SHARED_LIBS 变量，则默认为 STATIC。
因此，如果发现一个项目里的 add_library 都是无参数的，意味着你可以用：
cmake -B build -DBUILD_SHARED_LIBS:BOOL=ON
来让他全部生成为动态库

#对象库类似于静态库，但不生成 .a 文件，只由 CMake 记住该库生成了哪些对象文件
#对象库是 CMake 自创的，绕开了编译器和操作系统的各种繁琐规则，保证了跨平台统一性。
#在自己的项目中，我推荐全部用对象库(OBJECT)替代静态库(STATIC)避免跨平台的麻烦。
#对象库仅仅作为组织代码的方式，而实际生成的可执行文件只有一个，减轻了部署的困难。
add_library(mylib OBJECT mylib.cpp
)
add_executable(utils_test ${source})
target_link_libraries(utils_test PRIVATE mylib)

find_package(Python REQUIRED)
enable_testing()
add_test(NAME utils_test COMMAND $<TARGET_FILE:utils_test>)
add_test(pytest ${Python_EXECUTABLE} pytest.py)


#将main的可执行程序作为run来运行,不用再进入build了！！！
add_custom_target(run COMMAND $<TARGET_FILE:main>)


#生成器表达式
语法：$<$<类型:值>:为真时的表达式>
比如 $<$<PLATFORM_ID:Linux,Darwin>:MY_NAME=”Unix Like”>
在 Windows 平台上会变为 MY_NAME=”Bill Gates”
其他平台上则表现为空字符串

#include 的 XXX.cmake 没有独立作用域
#add_subdirectory 的 CMakeLists.txt 有独立作用域
#macro 没有独立作用域
#function 有独立作用域

#set_target_properties 批量设置多个属性
set_target_properties(foo PROPERTIES
  PUBLIC_HEADER "foo.h;${CMAKE_CURRENT_BINARY_DIR}/config.h")
install(TARGETS foo
  # IMPORTANT: Add the foo library to the "export-set"
  EXPORT FooBarTargets
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/foo"
    COMPONENT dev)
