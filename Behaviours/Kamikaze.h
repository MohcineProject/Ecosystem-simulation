//
// Created by mouha1505 on 29/11/24.
//

#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Behaviour.h"

// Kamikaze class that inherits from Behaviour. Represents a behaviour where the Bestiole
// takes a reckless approach towards a target, typically moving directly towards it.
class Kamikaze : public Behaviour {
    double calculateNewDirection(const Bestiole* closestBestiolePtr);

    public:
    Kamikaze(Bestiole *bestiole) ;
    ~Kamikaze() = default;
    void doBehaviour(std::set<Bestiole*> &neighbors) override;
    std::string getType() override{return type;}
};

#endif //KAMIKAZE_H
