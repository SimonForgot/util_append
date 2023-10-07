if [ -z "$1" ]; then

  rm -f ./build/CMakeCache.txt
  INSTALL_LOC=./install
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release --trace-source=FindMPI.cmake \
    -DCMAKE_VERBOSE_MAKEFILE=OFF \
    -DMPI_HOME=~/app/openMPI \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_LOC

elif [ $1 = "c" ]; then

  cpu_count=$(grep -c ^processor /proc/cpuinfo)
  cmake --build build -j ${cpu_count}

elif [ $1 = "i" ]; then

  rm -rf $INSTALL_LOC
  cmake --install build
elif [ $1 = "r" ]; then

  cmake --build build --target run
fi

#ctest -j 12

