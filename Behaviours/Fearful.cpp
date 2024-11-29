//
// Created by mouha1505 on 28/11/24.
//

#include "Fearful.h"
#include "../Bestiole.h"

const int Fearful::DENSITE_BESTIOLE = 2;
const double Fearful::COEF_FPEUR = 3. ;

double Fearful::calculateNewDirection(Bestiole& bestiole, const std::vector<Bestiole>& neighbors) {
    if (neighbors.empty())
        return bestiole.getOrientation();

    // Calcul du barycentre des neighbors proches
    double sumX = 0.0, sumY = 0.0;
    for (const auto& neighbor : neighbors) {
        sumX += neighbor.getCoordx();
        sumY += neighbor.getCoordy();
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


void Fearful::doBehaviour(Bestiole& bestiole, const std::vector<Bestiole>& neighbors){
    if (neighbors.size() >= DENSITE_BESTIOLE) {
        bestiole.setOrientation(calculateNewDirection(bestiole, neighbors));
        bestiole.setVitesse(bestiole.getVitesse() * COEF_FPEUR);
    }
    else {
        bestiole.setVitesse(bestiole.getVitesse());
    }
  }

