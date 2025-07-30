
#include "Fearful.h"
#include "../Bestiole.h"

const int Fearful::DENSITE_BESTIOLE = 1;
const double Fearful::COEF_FPEUR = 3. ;

Fearful::Fearful(Bestiole *bestiole) {
    this->bestiole = bestiole;
    this -> type = "Fearful";
}


double Fearful::calculateNewDirection(const std::set<Bestiole*>& neighbors) {
    if (neighbors.empty())
        return this->bestiole->getOrientation();

    // Calcul du barycentre des neighbors proches
    double sumX = 0.0, sumY = 0.0;
    for (const auto& neighbor : neighbors) {
        sumX += neighbor -> getCoordx();
        sumY += neighbor -> getCoordy();
    }
    double meanX = sumX / neighbors.size(); // x of the barycentre
    double meanY = sumY / neighbors.size(); // y of the barycentre

    // Direction à adopter pour aller à l'opposé du barycentre
    double dx = meanX - bestiole->getCoordx();
    double dy = meanY - bestiole->getCoordy();

    if (dx == 0 && dy == 0) {
        // if Barycentre position == bestiole position, keep the same orientation for the bestiole
        return bestiole->getOrientation();
    }

    return M_PI - atan2(dy, dx);  // take the opposite direction
}


void Fearful::doBehaviour(std::set<Bestiole*>& neighbors){

    if (neighbors.size() < DENSITE_BESTIOLE) {
        // If the density is low, reset to base speed
        bestiole->setVitesse(bestiole->getBaseSpeed());
        return;
    }
    // If the density is high, calculate new direction and adjust speed
    bestiole->setOrientation(calculateNewDirection(neighbors));

    // compute the new sped
    double adjustedSpeed = bestiole->getBaseSpeed() * COEF_FPEUR;

    // adjust the speed of the bestiole to not go over the max speed
    bestiole->setVitesse(std::min(adjustedSpeed, bestiole->getMaxSpeed()));
  }

