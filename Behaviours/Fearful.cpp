//
// Created by mouha1505 on 28/11/24.
//

#include "Fearful.h"
#include "../Bestiole.h"

const int Fearful::DENSITE_BESTIOLE = 2;
const double Fearful::COEF_FPEUR = 3. ;

double Fearful::calculateNewDirection(Bestiole& bestiole, const std::set<Bestiole*>& neighbors) {
    if (neighbors.empty())
        return bestiole.getOrientation();

    // Calcul du barycentre des neighbors proches
    double sumX = 0.0, sumY = 0.0;
    for (const auto& neighbor : neighbors) {
        sumX += neighbor -> getCoordx();
        sumY += neighbor -> getCoordy();
    }
    double meanX = sumX / neighbors.size();
    double meanY = sumY / neighbors.size();

    // Direction à adopter pour aller à l'opposé du barycentre
    double dx = meanX - bestiole.getCoordx();
    double dy = meanY - bestiole.getCoordy();

    if (dx == 0 && dy == 0) {
        // Barycentre coïncide avec la bestiole, on garde l'orientation actuelle
        return bestiole.getOrientation();
    }

    return atan2(-dy, -dx);
}


void Fearful::doBehaviour(Bestiole& bestiole, const std::set<Bestiole*>& neighbors){
    if (neighbors.size() < DENSITE_BESTIOLE) {
        // If the density is low, reset to base speed
        bestiole.setVitesse(bestiole.getBaseSpeed());
        return;
    }
    // If the density is high, calculate new direction and adjust speed
    bestiole.setOrientation(calculateNewDirection(bestiole, neighbors));

    double adjustedSpeed = bestiole.getBaseSpeed() * COEF_FPEUR;
    bestiole.setVitesse(std::min(adjustedSpeed, bestiole.getMaxSpeed()));
  }

