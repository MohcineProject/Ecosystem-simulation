//
// Created by mouha1505 on 29/11/24.
//

#include "Behaviour.h"
#include "../Bestiole.h"

Bestiole* Behaviour::closestBestiole(const Bestiole &bestiole, const std::set<Bestiole>& neighbors) {
    double minDistanceSquared = 1000000000;
    Bestiole* closestBestiolePtr = nullptr;

    for (const auto& neighbor : neighbors) {
        double currentDistanceSquared = std::pow(neighbor.getCoordx() - bestiole.getCoordx(), 2) +
                                         std::pow(neighbor.getCoordy() - bestiole.getCoordy(), 2);
        if (currentDistanceSquared < minDistanceSquared) {
            closestBestiolePtr = const_cast<Bestiole*>(&neighbor); // Point to the current closest neighbor
            minDistanceSquared = currentDistanceSquared;
        }
    }

    return closestBestiolePtr;
}
