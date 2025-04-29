@echo off
set INSTALL_DIR="C:/Program Files/Autodesk/3ds Max 2023/Python"

if "%1"=="" (
    RMDIR /S /Q build
    ::vs2017 :"Visual Studio 15 2017 Win64"    
    ::vs2019 :"Visual Studio 16 2019" -A x64
    ::vs2022 :"Visual Studio 17 2022" -A x64
    cmake -Bbuild -G "Visual Studio 17 2022" -A x64 ^
    -DMAXSDK="C:\Program Files\Autodesk\3ds Max 2023 SDK\maxsdk" ^
    -Dpybind11_DIR="D:\repo\pybind11-2.13.6\install\share\cmake\pybind11" ^
    -DPython_ROOT_DIR="D:\repo\pythons\py3_9_7" ^
    -DCMAKE_INSTALL_PREFIX=%INSTALL_DIR%
)else if "%1"=="c" (
    cmake --build build -j36 --config Release --clean-first
)else if "%1"=="i" (
    cmake --install build
)else if "%1"=="r" (
    cmake --build build --target run --config Release
)

::build & install command
::cmake --build build -j36 --target install --config Release