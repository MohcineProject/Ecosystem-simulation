//
// Created by mouha1505 on 05/12/24.
//

#include "MultipleBehaviour.h"


MultipleBehaviour::MultipleBehaviour(const std::vector<std::shared_ptr<Behaviour>> &availableBehaviours, int interval): behaviours(availableBehaviours),
                                                                                                                        currentBehaviour(availableBehaviours.front()),
                                                                                                                        switchInterval(interval),
                                                                                                                        stepCounter(0) {// Seed for random behaviour selection
}

void MultipleBehaviour::switchToRandomBehaviour() {
    if (behaviours.size() > 1) {
        std::shared_ptr<Behaviour> newBehaviour;
        do {
            newBehaviour = behaviours[std::rand() % behaviours.size()];
        } while (newBehaviour == currentBehaviour); // Avoid picking the same behaviour
        currentBehaviour = newBehaviour;
    }
}

void MultipleBehaviour::doBehaviour(Bestiole &bestiole, const std::vector<Bestiole> &neighbors) {
    // Perform the current behaviour
    currentBehaviour->doBehaviour(bestiole, neighbors);

    // Increment the step counter
    stepCounter++;

    // Check if it's time to switch behaviours
    if (stepCounter >= switchInterval) {
        switchToRandomBehaviour();
        stepCounter = 0; // Reset the counter
    }
}
