
#include "MultipleBehaviour.h"

#include "Cautious.h"
#include "Gregarious.h"
#include "Kamikaze.h"

/**
 * @brief Static variable for controlling how frequently behaviors switch.
 */
int MultipleBehaviour::switchInterval = 20;

/**
 * @brief Constructor for the "MultipleBehaviour" class. Initializes the list of behaviors for the "Bestiole".
 *
 * @param bestiole Pointer to the "Bestiole" this behavior is associated with.
 * @param behaviourNames A vector of behavior names to assign to the "Bestiole".
 */
MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames): behaviourNames(behaviourNames),
                                                                                                                        stepCounter(0) {
    // Store the reference to the Bestiole object
    this->bestiole = bestiole;
    // Loop through the provided behaviour names
    for (const auto& name : behaviourNames) {
        // Create the corresponding behaviour objects and store them in the behaviours vector
        if (name == "Cautious") {
        behaviours.push_back(std::make_unique<Cautious>(bestiole));
        } else if (name == "Fearful") {
            behaviours.push_back(std::make_unique<Fearful>(bestiole));
        } else if (name == "Kamikaze") {
            behaviours.push_back(std::make_unique<Kamikaze>(bestiole));
        } else if (name == "Gregaire") {
            behaviours.push_back(std::make_unique<Gregarious>(bestiole));
        }
    }
    // If no behaviours were added, default to all available behaviours
    if (behaviours.empty()) {
        behaviours.push_back(std::make_unique<Cautious>(bestiole));
        behaviours.push_back(std::make_unique<Fearful>(bestiole));
        behaviours.push_back(std::make_unique<Kamikaze>(bestiole));
        behaviours.push_back(std::make_unique<Gregarious>(bestiole));
    }
    currentBehaviour = behaviours.front().get(); // Set the current behaviour to the first in the list
    this -> type = "Multiple";                   // Set the type to indicate this is a MultipleBehaviour instance
}

/**
 * @brief Overloaded constructor for "MultipleBehaviour" that assigns default behaviors.
 * if no specific behaviour names are provided.
 * @param bestiole Pointer to the "Bestiole" this behavior is associated with.
 */
MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole)
    : MultipleBehaviour(bestiole, std::vector<std::string>{}) {}

/**
 * @brief Switches the "Bestiole" to a randomly selected behavior, ensuring it is different from the current one.
 */
void MultipleBehaviour::switchToRandomBehaviour() {
    // Ensure there is more than one behaviour to switch to
    if (behaviours.size() > 1) {
        Behaviour* newBehaviour;
        // Keep picking a random behaviour until it's different from the current one
        do {
            newBehaviour = behaviours[std::rand() % behaviours.size()].get();
        } while (newBehaviour == currentBehaviour); // Avoid picking the same behaviour
        currentBehaviour = newBehaviour;            // Update the current behavior to the new randomly chosen behaviour
    }
}

/**
 * @brief Executes the current behavior and handles the logic for switching behaviors at intervals.
 *
 * @param neighbors A set of pointers to neighboring "Bestiole" objects.
 */
void MultipleBehaviour::doBehaviour(std::set<Bestiole*> &neighbors) {
    // Perform the current behaviour
    currentBehaviour->doBehaviour(neighbors);

    // Increment the step counter
    stepCounter++;

    // Check if it's time to switch behaviours
    if (stepCounter >= switchInterval) {
        switchToRandomBehaviour();
        stepCounter = 0; // Reset the counter
    }
}

/**
 * @brief Retrieves the current behavior of the "Bestiole".
 *
 * @return A pointer to the current "Behaviour" object.
 */
Behaviour * MultipleBehaviour::getBehaviour() const {
    return this -> currentBehaviour;
}
