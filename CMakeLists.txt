cmake_minimum_required(VERSION 3.29)
project(BEproject)

set(CMAKE_CXX_STANDARD 11)

add_executable(BEproject main.cpp
        Aquarium.cpp
        Bestiole.cpp
        CImg.h
        Milieu.cpp
        ICapteur.h
        CapteurS.cpp
        CapteurS.h
        CapteurV.cpp
        CapteurV.h
)


