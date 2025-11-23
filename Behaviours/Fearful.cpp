
#include "Fearful.h"
#include "Bestioles/Bestiole.h"

const int Fearful::DENSITE_BESTIOLE = 1;
const double Fearful::FEAR_FACTOR = 3. ;

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
    // If density is low (fewer neighbors than threshold), reset to normal speed
    if (neighbors.size() < DENSITE_BESTIOLE) {
        bestiole->setBehaviorSpeedMultiplier(1.0);
        return;
    }
    
    // If density is high (at least DENSITE_BESTIOLE neighbors), flee and increase speed
    // Calculate new direction away from neighbors
    bestiole->setOrientation(calculateNewDirection(neighbors));
    
    // Apply fear factor multiplier (3x speed when fleeing)
    // getActualSpeed() will cap the final speed at MAX_VITESSE if needed
    bestiole->setBehaviorSpeedMultiplier(FEAR_FACTOR);
}

