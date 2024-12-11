//
// Created by mouha1505 on 29/11/24.
//

#ifndef CAUTIOUS_H
#define CAUTIOUS_H

#include <memory>
#include "Behaviour.h"

class Bestiole;

class Cautious : public Behaviour {

    double calculateNewDirection(const Bestiole* closestBestiolePtr);

    public:
    Cautious(Bestiole* bestiole);
    ~Cautious() = default;
    void doBehaviour(std::set<Bestiole*> &neighbors) override;
    std::string getType() override{return type;}
};

#endif //CAUTIOUS_H
