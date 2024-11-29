//
// Created by mouha1505 on 29/11/24.
//

#include "Cautious.h"
#include "../Bestiole.h"

#include <cmath>

// Find the closest bestiole in a vector of Bestiole objects
Bestiole* Cautious::closestBestiole(const Bestiole &bestiole, const std::vector<Bestiole>& neighbors) {
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

// Calculate the new direction to avoid collision
double Cautious::calculateNewDirection(const Bestiole& bestiole, const Bestiole* closestBestiolePtr) {
    if (!closestBestiolePtr) {
        return bestiole.getOrientation(); // Keep current orientation if no close bestiole
    }

    double dx = closestBestiolePtr->getCoordx() - bestiole.getCoordx();
    double dy = closestBestiolePtr->getCoordy() - bestiole.getCoordy();
    double newOrientation = M_PI / 2 - atan2(dx, dy); // Angle to avoid collision
    return newOrientation;
}

// Override doBehaviour to adjust trajectory dynamically
void Cautious::doBehaviour(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) {
    if (neighbors.empty()) {
        return; // No neighbors, no behavior to execute
    }

    // Find the closest bestiole
    const Bestiole* closestBestiolePtr = closestBestiole(bestiole,neighbors);

    // Calculate new orientation to avoid collision
    double newOrientation = calculateNewDirection(bestiole, closestBestiolePtr);

    // Update the bestiole's orientation
    bestiole.setOrientation(newOrientation);
}

