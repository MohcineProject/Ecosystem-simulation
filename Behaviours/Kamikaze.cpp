//
// Created by mouha1505 on 29/11/24.
//

#include "Kamikaze.h"
#include "../Bestiole.h"

Kamikaze::Kamikaze(Bestiole *bestiole) {
    this->bestiole = bestiole;
}


double Kamikaze::calculateNewDirection(const Bestiole *closestBestiolePtr) {
    if (!closestBestiolePtr) {
        return bestiole->getOrientation(); // Keep current orientation if no close bestiole
    }

    double dx = closestBestiolePtr->getCoordx() - bestiole->getCoordx();
    double dy = closestBestiolePtr->getCoordy() - bestiole->getCoordy();

    // Compute the orientation
    double nouvelleOrientation = M_PI / 2 + (dy != 0 ? atan2(dy, dx) : (dx > 0 ? 0 : M_PI));

    return nouvelleOrientation + M_PI; // Reverse direction
}

void Kamikaze::doBehaviour(std::set<Bestiole*> &neighbors) {
    if (neighbors.empty()) {
        return; // No neighbors, no behavior to execute
    }

    // Find the closest bestiole
    const Bestiole* closestBestiolePtr = closestBestiole(neighbors);

    // Calculate new orientation to avoid collision
    double newOrientation = calculateNewDirection(closestBestiolePtr);

    // Update the bestiole's orientation
    bestiole->setOrientation(newOrientation);
}
