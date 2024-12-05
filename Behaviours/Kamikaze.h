//
// Created by mouha1505 on 29/11/24.
//

#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Behaviour.h"

class Kamikaze : public Behaviour {
    static double calculateNewDirection(const Bestiole& bestiole, const Bestiole* closestBestiolePtr);

    public:
    Kamikaze() = default;
    void doBehaviour(Bestiole &bestiole, const std::vector<Bestiole> &neighbors) override;

};

#endif //KAMIKAZE_H
