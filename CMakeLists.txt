﻿cmake_minimum_required(VERSION 3.16)
project(Plutus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widget Sql)

add_subdirectory(external)
add_subdirectory(kernel)
add_subdirectory(core)
add_subdirectory(database)
add_subdirectory(modules)
