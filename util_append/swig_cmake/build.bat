::clean previous build files
RMDIR /S /Q build

::specify which cmake generator to use
::vs2017 :"Visual Studio 15 2017 Win64"    
::vs2019 :"Visual Studio 16 2019" -A x64
::vs2022 :"Visual Studio 17 2022" -A x64
cmake -Bbuild -G "Visual Studio 16 2019" -A x64 ^
-DMAYA_VERSION=2019 ^
-DZLIB_ROOT=D:/app/zlib ^
-DZLIB_USE_STATIC_LIBS=ON ^
-DCNPY_DIR=D:/app/cnpy ^
-DPython_EXECUTABLE="C:/Program Files/Autodesk/Maya2019/bin/mayapy.exe" ^
-DPython_LIBRARY="C:/Program Files/Autodesk/Maya2019/lib/python27.lib" ^
-DPython_INCLUDE_DIR="C:/Program Files/Autodesk/Maya2019/include/python2.7" ^
-DSWIG_EXECUTABLE="D:/app/swigwin-4.0.2/swig.exe" ^
-DCMAKE_INSTALL_PREFIX=D:/repo/deepbodyrig/VertexSetCmd/install

::build & install command
::cmake --build build -j12 --target install --config Release