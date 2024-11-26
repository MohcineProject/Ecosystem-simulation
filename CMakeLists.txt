cmake_minimum_required(VERSION 3.29)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp
        Aquarium.cpp
        Bestiole.h
        Bestiole.cpp
        Aquarium.h
        Milieu.cpp
        CImg.h)
