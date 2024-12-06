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

class MultipleBehaviour : public Behaviour {

    std::vector<std::shared_ptr<Behaviour>> behaviours;
    std::vector<std::string> behaviourNames;
    std::shared_ptr<Behaviour> currentBehaviour;
    static int switchInterval;
    int stepCounter;

    // Function to switch to a random behaviour
    void switchToRandomBehaviour();
public:
    // Constructor: takes a list of behaviours and a switch interval
    MultipleBehaviour(Bestiole *bestiole, const std::vector<std::string> &behaviourNames);
    MultipleBehaviour(Bestiole *bestiole);
    void doBehaviour(std::set<Bestiole*>& neighbors) override;

    Behaviour *getBehaviour() const;
};

#endif //MULTIPLEBEHAVIOUR_H
