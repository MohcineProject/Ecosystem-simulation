cmake_minimum_required(VERSION 3.29)
project(BE-aquarium)

set(CMAKE_CXX_STANDARD 20)

# Set compiler warnings
add_compile_options(-Wall)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Add the executable
add_executable(BE-aquarium
        main.cpp
        Aquarium.cpp
        Bestiole.h
        Bestiole.cpp
        Aquarium.h
        Milieu.cpp
        CImg.h
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
        Test/CreateBestioleForTest.h
        Test/CreateBestioleForTest.cpp
        Behaviours/Kamikaze.h
        Behaviours/Kamikaze.cpp
        Test/KamikazeTest.h
        Test/KamikazeTest.cpp
        Test/CautiousTest.h
        Test/CautiousTest.cpp
        Test/FearfulTest.h
        Test/FearfulTest.cpp
        Test/GregaireTest.h
        Test/GregaireTest.cpp
)

# Link required libraries
target_link_libraries(BE-aquarium X11)
