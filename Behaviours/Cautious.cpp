//
// Created by mouha1505 on 29/11/24.
//

#include "Cautious.h"
#include "../Bestiole.h"

#include <cmath>

// Find the closest bestiole in a set of Bestiole objects

// Calculate the new direction to avoid collision
double Cautious::calculateNewDirection( const Bestiole* closestBestiolePtr) {
    if (!closestBestiolePtr) {
        return bestiole ->getOrientation(); // Keep current orientation if no close bestiole
    }

    double dx = closestBestiolePtr->getCoordx() - bestiole ->getCoordx();
    double dy = closestBestiolePtr->getCoordy() - bestiole->getCoordy();
    double newOrientation = atan2(dx, dy) + M_PI; // Angle to avoid collision
    return newOrientation;
}

Cautious::Cautious(Bestiole *bestiole) {
    this -> bestiole = bestiole;
    this -> type = "Cautious";
}

// Override doBehaviour to adjust trajectory dynamically
void Cautious::doBehaviour(std::set<Bestiole*>& neighbors) {
    if (neighbors.empty()) {
        return; // No neighbors, no behavior to execute
    }

    // Find the closest bestiole
    const Bestiole* closestBestiolePtr = closestBestiole(neighbors);

    // Calculate new orientation to avoid collision
    double newOrientation = calculateNewDirection(closestBestiolePtr);

    // Update the bestiole's orientation
    bestiole -> setOrientation(newOrientation);
}

