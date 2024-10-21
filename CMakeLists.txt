cmake_minimum_required(VERSION 3.16)
project(Plutus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

add_subdirectory(kernel)
add_subdirectory(core)
add_subdirectory(test/core)
