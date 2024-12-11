cmake_minimum_required(VERSION 3.29)
project(BEproject)


set(CMAKE_CXX_STANDARD 14)

add_executable(BEproject main.cpp
        Aquarium.cpp
        Bestiole.cpp
        Bestiole.h
        CImg.h
        Milieu.cpp
        ICapteur.h
        CapteurS.cpp
        CapteurS.h
        CapteurV.cpp
        CapteurV.h
        Carapace.cpp
        Carapace.h
        Fins.cpp
        Fins.h
        Camouflage.cpp
        Camouflage.h
        Behaviours/Behaviour.h
        Behaviours/Behaviour.cpp
        Behaviours/Gregaire.h
        Behaviours/Gregaire.cpp
        Behaviours/Fearful.h
        Behaviours/Fearful.cpp
        Behaviours/Cautious.h
        Behaviours/Cautious.cpp
        Behaviours/MultipleBehaviour.h
        Behaviours/MultipleBehaviour.cpp
        Behaviours/Kamikaze.cpp)



