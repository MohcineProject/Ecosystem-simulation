
#include "MultipleBehaviour.h"

#include "Cautious.h"
#include "Gregaire.h"
#include "Kamikaze.h"

int MultipleBehaviour::switchInterval = 20;

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames): behaviourNames(behaviourNames),
                                                                                                                        stepCounter(0) {
    this->bestiole = bestiole;
    for (const auto& name : behaviourNames) {
        if (name == "Cautious") {
            behaviours.push_back(std::make_shared<Cautious>(bestiole));
        } else if (name == "Fearful") {
            behaviours.push_back(std::make_shared<Fearful>(bestiole));
        } else if (name == "Kamikaze") {
            behaviours.push_back(std::make_shared<Kamikaze>(bestiole));
        } else if (name == "Gregaire") {
            behaviours.push_back(std::make_shared<Gregaire>(bestiole));
        }
    }
    if (behaviours.empty()) {
        behaviours.push_back(std::make_shared<Cautious>(bestiole));
        behaviours.push_back(std::make_shared<Fearful>(bestiole));
        behaviours.push_back(std::make_shared<Kamikaze>(bestiole));
        behaviours.push_back(std::make_shared<Gregaire>(bestiole));
    }
    currentBehaviour = behaviours.front();
    this -> type = "MultipleBehaviour";
}

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole)
    : MultipleBehaviour(bestiole, std::vector<std::string>{}) {}

void MultipleBehaviour::switchToRandomBehaviour() {
    if (behaviours.size() > 1) {
        std::shared_ptr<Behaviour> newBehaviour;
        do {
            newBehaviour = behaviours[std::rand() % behaviours.size()];
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
    return this -> currentBehaviour.get();
}
