cmake_minimum_required(VERSION 3.16)
project(Plutus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

enable_testing(true)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widget Test)

add_subdirectory(kernel)
add_subdirectory(core)
add_subdirectory(test)
