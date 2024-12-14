//
// Created by mouha1505 on 05/12/24.
//

#ifndef MULTIPLEBEHAVIOUR_H
#define MULTIPLEBEHAVIOUR_H

#include <memory>
#include <set>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Behaviour.h"
#include "../Bestiole.h"


// The MultipleBehaviour class represents a behaviour that can switch between multiple sub-behaviours.
// It extends the Behaviour base class and allows a Bestiole to dynamically change its behaviour.
class MultipleBehaviour : public Behaviour {

    // A list of behaviours that the MultipleBehaviour can switch between.
    std::vector<std::unique_ptr<Behaviour>> behaviours;
    // Names of the behaviours in string format for initialization and identification.
    std::vector<std::string> behaviourNames;
    Behaviour* currentBehaviour;
    // A static variable that defines how often (in steps) the behaviour should switch.
    static int switchInterval;
    // Counter to track the number of steps since the last switch.
    int stepCounter;

    // Function to switch to a random behaviour
    void switchToRandomBehaviour();
public:
    // Constructor: Initializes the MultipleBehaviour with a given Bestiole
    // and a list of behaviour names to instantiate corresponding behaviour objects.
    MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames);

    // Constructor: Initializes the MultipleBehaviour with default behaviours
    // if no specific behaviour names are provided.
    MultipleBehaviour(Bestiole *bestiole);


    // Overrides the doBehaviour method from the Behaviour base class.
    // Executes the current behaviour, and switches to another behaviour if needed.
    void doBehaviour(std::set<Bestiole*>& neighbors) override;

    Behaviour *getBehaviour() const;
    std::string getType() override{return type;}
};

#endif //MULTIPLEBEHAVIOUR_H
