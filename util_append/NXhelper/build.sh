if [ -z "$1" ]; then
  INSTALL_LOC=/home/zhangxinlong/simon/apps/NXhelper
  rm -f ./build/CMakeCache.txt
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -GNinja \
        -DARNOLD_ROOT=/home/zhangxinlong/simon/apps/Arnold-6.0.2.1 \
        -DNXRENDERER_ROOT=/home/zhangxinlong/simon/apps/NX \
        -DCMAKE_INSTALL_PREFIX=${INSTALL_LOC} \
        -DCMAKE_MODULE_PATH=CMake_Modules

elif [ $1 = "c" ]; then

  cmake --build build -j12

elif [ $1 = "i" ]; then

  rm -rf ${INSTALL_LOC}
  cmake --install build
elif [ $1 = "r" ]; then

  cmake --build build --target run
fi

#ctest -j 12