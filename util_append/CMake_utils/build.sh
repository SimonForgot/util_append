if [ -z "$1" ]; then

  rm -f ./build/CMakeCache.txt
  INSTALL_LOC=./install
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DBOOST_ROOT=~/app/gaffer-build \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_LOC

elif [ $1 = "c" ]; then

  cpu_count=$(grep -c ^processor /proc/cpuinfo)
  cmake --build build -j ${cpu_count}

elif [ $1 = "i" ]; then

  rm -rf $INSTALL_LOC
  cmake --install build
elif [ $1 = "r" ]; then
  export LD_LIBRARY_PATH=/home/zhangxinlong/repo/test/testcpp/IE_RTTI/build:~/app/gaffer-build/lib
  cmake --build build --target run
fi

#ctest -j 12


