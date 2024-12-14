//
// Created by mouha1505 on 29/11/24.
//

#ifndef CAUTIOUS_H
#define CAUTIOUS_H

#include <memory>
#include "Behaviour.h"

class Bestiole;


// Cautious class inherits from Behaviour. Represents a behaviour where the Bestiole
// acts cautiously, avoiding collision with other Bestioles.
class Cautious : public Behaviour {

    double calculateNewDirection(const Bestiole* closestBestiolePtr); // method to compute the new direction

    public:
    Cautious(Bestiole* bestiole);
    ~Cautious() = default;
    // Overrides the doBehaviour method from the Behaviour base class.
    void doBehaviour(std::set<Bestiole*> &neighbors) override;
    std::string getType() override{return type;}
};

#endif //CAUTIOUS_H
