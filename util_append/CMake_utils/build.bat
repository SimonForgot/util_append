::comments
@echo off

set INSTALL_DIR="./install"
if "%1"=="" (
    DEL .\build\CMakeCache.txt
    cmake -S. -Bbuild  ^
    -G"Visual Studio 17 2022" -Win64
) ^

else if "%1"=="c" (
    cmake --build build -j8 --clean-first --config Release
) ^

else if "%1"=="i" (
    cmake --install build --prefix %INSTALL_DIR%  
) ^

else if "%1"=="r" (
    cmake --build build --target run
) ^
