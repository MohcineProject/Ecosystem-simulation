
#include "MultipleBehaviour.h"

#include "Cautious.h"
#include "Gregarious.h"
#include "Kamikaze.h"
#include "Fearful.h"

int MultipleBehaviour::switchInterval = 20;

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames): behaviourNames(behaviourNames),
                                                                                                                           stepCounter(0) {
    this->bestiole = bestiole;

    // Assigns the behaviors as defined in the behaviourNames list
    for (const auto& name : behaviourNames) {
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
    if (behaviours.empty()) {
        // If the behaviourNames is empty assign all behaviours
        behaviours.push_back(std::make_unique<Cautious>(bestiole));
        behaviours.push_back(std::make_unique<Fearful>(bestiole));
        behaviours.push_back(std::make_unique<Kamikaze>(bestiole));
        behaviours.push_back(std::make_unique<Gregarious>(bestiole));
    }

    // Assign the first behaviour to the current behaviour attribute
    currentBehaviour = behaviours.front().get();
    this -> type = "Multiple";
}

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole)
    : MultipleBehaviour(bestiole, std::vector<std::string>{}) {}


void MultipleBehaviour::switchToRandomBehaviour() {
    if (behaviours.size() > 1) {
        Behaviour* newBehaviour;
        do {
            newBehaviour = behaviours[std::rand() % behaviours.size()].get();
        } while (newBehaviour == currentBehaviour); // Avoid picking the same behaviour
        currentBehaviour = newBehaviour;
    }
}

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

Behaviour * MultipleBehaviour::getBehaviour() const {
    return this -> currentBehaviour;
}
