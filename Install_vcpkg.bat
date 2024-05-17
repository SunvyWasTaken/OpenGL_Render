@echo off
set currentPath=%cd%

ECHO Clone vcpkg
ECHO =============================
cmd /c git clone https://github.com/Microsoft/vcpkg.git

ECHO Initializing vcpkg
ECHO =============================
cmd /c "cd vcpkg && bootstrap-vcpkg.bat -disableMetrics"

ECHO Initializing vcpkg packages
ECHO =============================
cd vcpkg
vcpkg install

ECHO Initializing CMake project
ECHO =============================
cd %currentPath%
cmake -DCMAKE_TOOLCHAIN_FILE=%currentPath%/vcpkg/scripts/buildsystems/vcpkg.cmake -S %currentPath% -B %currentPath%/build

ECHO Transfer ressources files
ECHO =============================
xcopy .\DefaultApp\ressources\ .\build\DefaultApp\ressources\ /s /e

ECHO =============================
ECHO Install done
pause
