if [ -z "$1" ]; then

  rm -rf ./build
  INSTALL_LOC=./install
  MAYA_VERSION_NUM=2018
  cmake -Bbuild -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_LOC \
    -DMAYA_VERSION=$MAYA_VERSION_NUM \
    -DPython_EXECUTABLE=/usr/autodesk/maya$MAYA_VERSION_NUM/bin/mayapy \
    -DPython_LIBRARY=/usr/autodesk/maya$MAYA_VERSION_NUM/lib/python2.7 \
    -DPython_INCLUDE_DIR=/usr/autodesk/maya$MAYA_VERSION_NUM/include/python2.7

elif [ $1 = "c" ]; then

  cmake --build build -j12

elif [ $1 = "i" ]; then

  rm -rf $INSTALL_LOC
  cmake --install build
elif [ $1 = "r" ]; then

  cmake --build build --target run
fi

#ctest -j 12

