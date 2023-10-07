if [ -z "$1" ]; then

  rm -f ./build/CMakeCache.txt
  INSTALL_LOC=~/test
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release \
    -DBOOST_ROOT=/usr/local/usd_deps \
    -DBoost_USE_STATIC_LIBS=ON \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_LOC

elif [ $1 = "c" ]; then

  cmake --build build -j12

elif [ $1 = "i" ]; then

  rm -rf $INSTALL_LOC
  cmake --install build
elif [ $1 = "r" ]; then

  cmake --build build --target run
fi

#ctest -j 12

