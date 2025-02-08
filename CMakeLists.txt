cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(snake LANGUAGES CXX)
find_package(SDL3 CONFIG REQUIRED)
add_executable(snake
    src/main.cpp
    src/game_window.cpp
)
target_link_libraries(snake PRIVATE SDL3::SDL3)
