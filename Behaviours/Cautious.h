//
// Created by mouha1505 on 29/11/24.
//

#ifndef CAUTIOUS_H
#define CAUTIOUS_H

#include <memory>
#include "Behaviour.h"

class Bestiole;

class Cautious : public Behaviour {

    static double calculateNewDirection(const Bestiole& bestiole, const Bestiole* closestBestiolePtr);

    public:
    Cautious() = default;
    void doBehaviour(Bestiole &bestiole, const std::vector<Bestiole> &neighbors) override;
};

#endif //CAUTIOUS_H
