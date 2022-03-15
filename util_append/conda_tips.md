###test:使用自制的多版本conda包，创建conda环境。用于以后使用。


不得不说这也是个好思路，直接把C++库编译安装到`$CONDA_PREFIX`，
`cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX`
但是这样没有办法通过conda来一起管理，只能安装，不方便切换版本

`SET(CMAKE_CXX_COMPILER $ENV{CONDA_PREFIX}/bin/g++)`
在cmake里取得环境变量

###conda使用
conda avtivate env-name
conda search pkg-name
conda install pkg-name=version
conda install -c conda-forge cxx-compiler

