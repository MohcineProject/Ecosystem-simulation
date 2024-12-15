//
// Created by mouha1505 on 29/11/24.
//

#include "Behaviour.h"
#include "../Bestiole.h"



Bestiole* Behaviour::closestBestiole(const std::set<Bestiole*>& neighbors) {
    double minDistanceSquared = 1000000000;
    Bestiole* closestBestiolePtr = nullptr; // Initialize closestBestiolePtr to null ptr

    // for each neighbor
    for (const auto& neighbor : neighbors) {
        // Calculate the squared distance between the current "Bestiole" and its neighbor
        double currentDistanceSquared = std::pow(neighbor ->getCoordx() - bestiole -> getCoordx(), 2) +
                                         std::pow(neighbor -> getCoordy() - bestiole -> getCoordy(), 2);

        // retain the pointer to the closest bestiole
        if (currentDistanceSquared < minDistanceSquared) {
            closestBestiolePtr = neighbor; // Point to the current closest neighbor
            minDistanceSquared = currentDistanceSquared;
        }
    }

    // Return the pointer to the closest "Bestiole"
    return closestBestiolePtr;
}