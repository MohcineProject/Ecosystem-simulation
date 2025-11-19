//
// Created by mouha1505 on 29/11/24.
//

#include "Kamikaze.h"
#include "../Bestioles/Bestiole.h"

Kamikaze::Kamikaze(Bestiole *bestiole) {
    this->bestiole = bestiole;
    this -> type = "Kamikaze";
}


double Kamikaze::calculateNewDirection(const Bestiole *closestBestiolePtr) {
    // If there is no closest Bestiole (null pointer),
    // retain the current orientation of the Bestiole.
    if (!closestBestiolePtr) {
        return bestiole->getOrientation(); // Keep current orientation if no close bestiole
    }

    // Calculate the difference in x and y coordinates
    // between the current Bestiole and the closest Bestiole.
    double dx = closestBestiolePtr->getCoordx() - bestiole->getCoordx();
    double dy = closestBestiolePtr->getCoordy() - bestiole->getCoordy();

    // Compute the orientation
    // The result is negated to account for the coordinate bestiole's orientation.
    double nouvelleOrientation = -atan2(dy, dx);

    // Return the new orientation, which points directly at the closest Bestiole.
    return nouvelleOrientation ;
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
