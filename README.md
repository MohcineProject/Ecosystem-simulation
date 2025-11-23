# BE - Ecosystem Simulation

This project is a simulation of an ecosystem of creatures (we also call them **bestioles** as in French) in an aquarium, aiming to explore and demonstrate how different creatures interact when equipped with sensors, accessories, and various behaviors. The system simulates diverse behaviors of the creatures: gregarious, fearful, kamikaze, cautious, and with multiple personalities, while taking into account different sensors (such as eyes and ears) and accessories (such as fins, shells, and camouflage).

To adapt to the ecosystem, the creatures have evolved, for example by developing sensors, accessories, and certain special behaviors. Each creature possesses these attributes with random parameters.

The creatures will be simulated in a closed environment where they can collide with each other, which can result in their deaths. The creatures also have a randomly set age, represented as the number of steps they can move until they become dead.

---

## Features

### Sensors

- **Eyes**: The eyes allow the creature to see within an angular field in front of it.
- **Ears**: The ears enable the creature to hear all around it.

### Accessories

- **Fins**: Fins allow the equipped creature to move faster.
- **Shells**: A creature with a shell has a higher chance of surviving a collision but moves slower.
- **Camouflage**: A creature with camouflage becomes harder to detect by other creatures.

### Behaviors

- **Gregarious**: A gregarious creature adjusts its direction to align with the average direction of surrounding creatures.
- **Fearful**: When the number of surrounding creatures becomes too large, a fearful creature flees quickly in the opposite direction before resuming its normal speed.
- **Kamikaze**: A kamikaze creature is attracted to the nearest creature and tries to attack it by seeking a collision.
- **Cautious**: A cautious creature estimates the trajectories of nearby creatures and adjusts its path to avoid potential collisions.
- **Multiple Personalities**: A creature with multiple personalities successively adopts other randomly chosen behaviors over time. However, it remains a creature with multiple personalities.

---

## Design Patterns

The project implements the following design patterns:

- **Simple Factory with Singleton**: Used to provide a consistent and centralized way of producing creatures. It also abstracts away complicated functions like random selection of attributes.
- **Strategy**: Used for implementing different behaviors that a creature can adopt.
- **Composite**: Used for the Multiple Personalities behavior, where it is composed of multiple behaviors (leaves) which it uses to alternate a creature's personality.

---

## Usage

### Quick Start

- **Running**: Run `make launch` to build and run the simulation. This command will automatically download dependencies if needed.
- **Building**: Run `make` to compile the project. This command also downloads dependencies.
- **Testing**: Run `make test` to build and execute all unit tests (this will automatically set up Google Test if needed).
- **Dependencies**: Run `make get-deps` to manually download and set up all dependencies.

### Configuration

Enter the parameters of the simulation in the config file (`config.txt`).

#### Parameter Definitions

The following parameters define the valid ranges for creature attributes:

| Parameter | Range |
|----------|-------|
| `max vision capacity` | 0 < value < 1 |
| `max vision angle` | 0 < value < 360° |
| `max vision distance` | 0 < value < 200 |
| `max hearing distance` | 0 < value < 120 |
| `max hearing capacity` | 0 < value < 1 |
| `max camouflage capacity` | 0 < value < 1 |
| `max speed multiplier` | 0 < value < 1 |
| `max speed reductor` | 0 < value < 1 |
| `max resistance` | 0 < value < 1 |

> **Note**: To modify other parameters of Bestioles such as the number of Bestioles or other attributes, access and edit the corresponding values directly in the appropriate `.cpp` files.
