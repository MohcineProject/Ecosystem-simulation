cmake_minimum_required(VERSION 3.29)
project(BE-aquarium)

set(CMAKE_CXX_STANDARD 20)

add_executable(BE-aquarium main.cpp
        Aquarium.cpp
        Bestiole.h
        Bestiole.cpp
        Aquarium.h
        Milieu.cpp
        CImg.h
        Behaviours/Behaviour.h
        Behaviours/Gregaire.h
        Behaviours/Gregaire.cpp
        Behaviours/Fearful.h
        Behaviours/Fearful.cpp

)