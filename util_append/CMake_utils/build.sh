if [ -z "$1" ]; then

  rm -f ./build/CMakeCache.txt
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -GNinja \
    -DCMAKE_INSTALL_PREFIX=./install

elif [ $1 = "c" ]; then

  cmake --build build -j12

elif [ $1 = "i" ]; then

  rm -rf ./install
  cmake --install build
elif [ $1 = "r" ]; then

  cmake --build build --target run
fi

#ctest -j 12
