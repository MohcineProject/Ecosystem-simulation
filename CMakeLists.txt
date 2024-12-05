cmake_minimum_required(VERSION 3.29)
project(Be_cppp)

set(CMAKE_CXX_STANDARD 11)

add_executable(Be_cppp main.cpp
        Aquarium.cpp
        Bestiole.cpp
        Milieu.cpp
        Carapace.cpp
        Carapace.h
        Fins.cpp
        Fins.h
        Camouflage.cpp
        Camouflage.h)
