//
// Created by mouha1505 on 29/11/24.
//

#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Behaviour.h"

class Kamikaze : public Behaviour {
    double calculateNewDirection(const Bestiole* closestBestiolePtr);

    public:
    Kamikaze(Bestiole *bestiole) ;
    ~Kamikaze() = default;
    void doBehaviour(std::set<Bestiole*> &neighbors) override;

};

#endif //KAMIKAZE_H
