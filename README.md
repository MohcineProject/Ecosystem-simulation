# BE - Ecosystem simulation

This project is a simulation of an ecosystem of creatures (we also call them bestioles as in French) in an aquarium, aiming to explore and demonstrate how different creatures interact when equipped with sensors, accessories, and various behaviors. The system simulates diverse behaviors of the creatures: gregarious, fearful, kamikaze, cautious, and with multiple personalities, while taking into account different sensors (such as eyes and ears) and accessories (such as fins, shells, and camouflage).

To adapt to the ecosystem, the creatures have evolved, for example by developing sensors, accessories, and certain special behaviors. Each creature possesses these attributes with random parameters.

The creatures will be simulated in a closed environment where they can collide with each other, which can result in their deaths. The creatures also have a randomly set age, represented as the number of steps they can move until they become dead. 

Here is a list of the accessories, sensors, and behaviors implemented:

# Sensors:

    Eyes: The eyes allow the creature to see within an angular field in front of it.
    Ears: The ears enable the creature to hear all around it.

# Accessories:

    Fins: Fins allow the equipped creature to move faster.
    Shells: A creature with a shell has a higher chance of surviving a collision but moves slower.
    Camouflage: A creature with camouflage becomes harder to detect by other creatures.

# Behaviors:

    Gregarious: A gregarious creature adjusts its direction to align with the average direction of surrounding creatures.
    Fearful: When the number of surrounding creatures becomes too large, a fearful creature flees quickly in the opposite direction before resuming its normal speed.
    Kamikaze: A kamikaze creature is attracted to the nearest creature and tries to attack it by seeking a collision.
    Cautious: A cautious creature estimates the trajectories of nearby creatures and adjusts its path to avoid potential collisions.
    Multiple Personalities: A creature with multiple personalities successively adopts other randomly chosen behaviors over time. However, it remains a creature with multiple personalities.



# Design Patterns Used:

    Simple Factory with Singleton: Used to provide a consistent and centralized way of producing creatures. It also abstracts away complicated functions like random selection of attributes.
    Strategy: Used for implementing different behaviors that a creature can adopt.
    Composite: Used for the Multiple Personalities behavior, where it is composed of multiple behaviors (leaves) which it uses to alternate a creature's personality.

# Usage:

    1-Compilation with Makefile: Run make.
    2-Enter the parameters of the simulation in the config file ("config.txt")
    3-Execution of the Program: Run ./main.
    4-Defining Parameters:

    0 < max vision capacity < 1  
    0 < max vision angle < 360°  
    0 < max vision distance < 200  
    0 < max hearing distance < 120  
    0 < max hearing capacity < 1  
    0 < max camouflage capacity < 1  
    0 < max speed multiplier < 1  
    0 < max speed reductor < 1  
    0 < max resistance < 1  

To modify other parameters of Bestioles such as the number of Bestioles or other parameters, access and edit the corresponding values directly in the appropriate .cpp files.


