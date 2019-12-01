cmake_minimum_required(VERSION 3.2)

project(SFML_Demo)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(SFML_Demo main.cpp)
target_link_libraries(SFML_Demo sfml-graphics sfml-audio)