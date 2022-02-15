cmake_minimum_required(VERSION 3.19.2)
project(GitHub)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(GitHub
        cell_method.cpp
        cell_method.h
        emun.h
        main.cpp
        ship.cpp
        ship.h)
