###显示cmake的环境变量
`cmake --LAH ..`

###显示详细的编译信息
`make VERBOSE=1`

###target的private/interface/public属性
private代表这项设置是给本target自己用的，interface代表这是给调用本target的target用的(就和上条提到的h文件一样，都是暴露给外面的接口)，public是二者结合。
举个例子，我要build一个叫helloworld的so：
用到的cpp文件：
`add_library(helloworld SHARED ${CMAKE_SOURCE_DIR}/helloworld/helloworld.cpp)`
要用到的lib：
`target_link_libraries(helloworld PRIVATE hello world)`
我要导出的头文件（如果helloworld.h里面没有本target要用的东西的话):
`target_include_directories(helloworld INTERFACE ${CMAKE_SOURCE_DIR}/helloworld)`
如果是只有本cpp要include，就是PRIVATE，如果即是本CPP要用，也要对外暴露，就PUBLIC

PS:https://leimao.github.io/blog/CMake-Public-Private-Interface/ 讲得很好

***

对于include来说：
每一个target都有用来记录include信息`INCLUDE_DIRECTORIES` 和`INTERFACE_INCLUDE_DIRECTORIES`
其中前者用来自己用，后者专门留着给后来link它的target用，
`target_include_directories(<target> <PRIVATE> <item>)`只会将item append给前者，
`target_include_directories(<target> <INTERFACE> <item>)`只会将item append给后者，
PUBLIC版的则是append给二者都有

另外`target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <item>)`也会影响这两个量，
它会影响把<item>的后者发给前者的哪一部分，具体来说：
private只会把<item>的后者，交给<target>的前者，INTERFACE会把<item>的后者，交给<target>的后者，
PUBLIC会把<item>的后者，交给<target>的两者，
link关系的也是类似的，感觉这种机制中，都是有两个存储区，一块放拿来自己用的，另一块是留着给别人用的。private，interface和public只是用来说明应该把上一代传过来的留给别人用的东西放在自己的哪个存储区，还是说两个都放。


###cmake normal variable
对于cmake的普通变量来说， add_subdirectory()、function()会做值拷贝，想要访问上层变量就要set(... PARENT_SCOPE) ，而对于 include()、macro()来说，则是类似C语言的预处理过程，直接贴上去的。

###cmake cache variable
类似于全局变量，会被放进CMakeCache.txt，不删除的话，下次运行会读取的。
cmake -D var=value . 如果 CMake 中默认有这个 var Cache 变量，那么此时就是赋值，没有的话，CMake 就会默认创建了一个全局 Cache 变量然后赋值。

###获取 CACHE 缓存变量的值
`$CACHE{VAR}`
`globbing`：通配



###CMake常用变量和命令
ref：https://blog.csdn.net/dcrmg/article/details/103930432

使用`set_property(TARGET target1 target2 ... APPEND PROPERTY COMPILE_DEFINITIONS ...)`为多个目标设置相同的定义。

`target_compile_options(test PRIVATE -fvisibility=default)`增加编译选项
`target_compile_definitions(exe PRIVATE ZXL)`增加编译定义，即平时-DXXX 的XXX

(set CMAKE_CXX_STANDARD 17)设置C++标准

###编译链接相关

nm -C XXX 查看人能看懂的符号表
nm -CD XXX_查看人能看懂的动态链接符号表
readelf 查看elf文件信息    readelf -d .so 查看动态库的rpath和依赖的库
nm 符号表
ldd查看在当前环境下，so文件会找到的依赖位置

LD_PRELOAD环境变量，提前加载某个so
`$LD_PRELOAD="/data/preload/lib/malloc_interpose.so:/data/preload/lib/free_interpose.so" ls -lh`
这种方式可以只在执行某命令时使用某些so文件

###关于RPATH
https://dev.my-gate.net/2021/08/04/understanding-rpath-with-cmake/

在linux和mac下的不同之处
在linux，$ORIGIN表示在运行时，可运行文件的目录。mac的没仔细看。

objdump -x path/to/executable | grep RPATH
或readelf -d path/to/executable | head -20 
或chrpath -l path/to/executable
查看RPATH的值

如果原来的elf文件就设置了rpath，可以使用chrpath -r “\$\ORIGIN/path/to/library” <executable>来修改

使用patchelf实用程序尝试以下命令，它不会抱怨未设置的 rpath，并且会设置 RUNPATH 以实现类似的目标。【不过runpath的顺序优先级没有LD_LIBRARY_PATH诶】
`$ patchelf — set-rpath '$ORIGIN/path/to/library' <executable>`

##rpath可以单独为target设置！
set_target_properties(test_rpath PROPERTIES BUILD_RPATH "/home/zhangxinlong/repos/test_rpath/nx_trouble/build")
ref:https://blog.xizhibei.me/2021/02/12/a-brief-intro-of-rpath/

###以相对路径的方式设置RPATH（很适合作为标准的开发操作）
set_target_properties(test_rpath PROPERTIES INSTALL_RPATH $ORIGIN)#ORIGIN代表target的安装位置

###gcc选项：
-Wl,rpath=XXX
-Wl,-soname,libfoo.so
-Wl的作用是将它后面的选项传给链接器


如果可执行文件“foo”链接到共享库“bar”，则必须在执行可执行文件“foo”时找到并加载库“bar”。这是链接器的工作，在 Linux 下这通常是ld.so. 链接器在一组目录中搜索库栏，在大多数 UNIX 下，它的名称为libbar.so. 
链接器将按给定顺序搜索以下目录中的库：

RPATH- 链接到可执行文件的目录列表，大多数 UNIX 系统都支持。如果RUNPATH存在则忽略。
LD_LIBRARY_PATH - 保存目录列表的环境变量
RUNPATH- 与 相同RPATH，但经过 搜索LD_LIBRARY_PATH，仅在最新的 UNIX 系统上受支持，例如在大多数当前的 Linux 系统上
/etc/ld.so.conf-ld.so列出附加库目录的配置文件
内置目录 - 基本上/lib和/usr/lib

###在cmake里取得环境变量
`SET(CMAKE_CXX_COMPILER $ENV{CONDA_PREFIX}/bin/g++)`


###cmake的生成器
######负责从 CMakeLists.txt 生成本地构建系统构建规则文件的，称为生成器（generator）
作用是面向make，msvc，ninja这种build工具，所以它不需要指定项目的结构什么的这种构建阶段的东西
`cmake -P xxx.cmake` 执行cmake文件
`source_group()` 为IDE显示文件夹提供方便
`Findxxx.cmake  CMAKE_MODULE_PATH CMAKE_PREFIX_PATH`: 设置cmake的findpackage路径找对应的库


