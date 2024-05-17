@echo off

ECHO Initializing CMake project
ECHO =============================
cd %cd%
cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/vcpkg/scripts/buildsystems/vcpkg.cmake -S %cd% -B %cd%/build

ECHO Transfer ressources files
ECHO =============================
xcopy .\DefaultApp\ressources\ .\build\DefaultApp\ressources\ /s /e

ECHO =============================
ECHO Install done
pause