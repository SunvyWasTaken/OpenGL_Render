cmake_minimum_required (VERSION 3.10)

project("MiniMotor")
add_subdirectory(MiniMotor)
add_subdirectory(DefaultApp)

include("${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")