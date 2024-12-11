
#include "MultipleBehaviour.h"

#include "Cautious.h"
#include "Gregarious.h"
#include "Kamikaze.h"

int MultipleBehaviour::switchInterval = 20;

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames): behaviourNames(behaviourNames),
                                                                                                                        stepCounter(0) {
    this->bestiole = bestiole;
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
        behaviours.push_back(std::make_unique<Cautious>(bestiole));
        behaviours.push_back(std::make_unique<Fearful>(bestiole));
        behaviours.push_back(std::make_unique<Kamikaze>(bestiole));
        behaviours.push_back(std::make_unique<Gregarious>(bestiole));
    }
    currentBehaviour = behaviours.front().get();
    this -> type = "Multiple";
}

MultipleBehaviour::MultipleBehaviour(Bestiole *bestiole)
    : MultipleBehaviour(bestiole, std::vector<std::string>{}) {}

MultipleBehaviour::MultipleBehaviour(const MultipleBehaviour& other)
        : behaviourNames(other.behaviourNames),
          stepCounter(other.stepCounter) {
    // Deep copy behaviours
    for (const auto& behaviour : other.behaviours) {
        if (auto* cautious = dynamic_cast<Cautious*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Cautious>(*cautious));
        } else if (auto* fearful = dynamic_cast<Fearful*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Fearful>(*fearful));
        } else if (auto* kamikaze = dynamic_cast<Kamikaze*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Kamikaze>(*kamikaze));
        } else if (auto* gregaire = dynamic_cast<Gregarious*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Gregarious>(*gregaire));
        }
    }

    // Set currentBehaviour to the corresponding copy
    if (other.currentBehaviour) {
        auto it = std::find_if(
            other.behaviours.begin(), other.behaviours.end(),
            [&](const std::unique_ptr<Behaviour>& b) {
                return b.get() == other.currentBehaviour;
            });
        if (it != other.behaviours.end()) {
            currentBehaviour = behaviours[std::distance(other.behaviours.begin(), it)].get();
        }
    }
}

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

MultipleBehaviour& MultipleBehaviour::operator=(const MultipleBehaviour& other) {
    if (this == &other) return *this; // Self-assignment check

    behaviourNames = other.behaviourNames;
    stepCounter = other.stepCounter;

    // Deep copy behaviours
    behaviours.clear();
    for (const auto& behaviour : other.behaviours) {
        if (auto* cautious = dynamic_cast<Cautious*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Cautious>(*cautious));
        } else if (auto* fearful = dynamic_cast<Fearful*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Fearful>(*fearful));
        } else if (auto* kamikaze = dynamic_cast<Kamikaze*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Kamikaze>(*kamikaze));
        } else if (auto* gregaire = dynamic_cast<Gregarious*>(behaviour.get())) {
            behaviours.push_back(std::make_unique<Gregarious>(*gregaire));
        }
    }

    // Set currentBehaviour
    if (other.currentBehaviour) {
        auto it = std::find_if(
            other.behaviours.begin(), other.behaviours.end(),
            [&](const std::unique_ptr<Behaviour>& b) {
                return b.get() == other.currentBehaviour;
            });
        if (it != other.behaviours.end()) {
            currentBehaviour = behaviours[std::distance(other.behaviours.begin(), it)].get();
        }
    }
    return *this;
}
