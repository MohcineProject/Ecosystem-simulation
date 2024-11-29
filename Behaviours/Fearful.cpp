//
// Created by mouha1505 on 28/11/24.
//

#include "Fearful.h"
#include "../Bestiole.h"

const int Fearful::DENSITE_BESTIOLE = 2;
const double Fearful::COEF_FPEUR = 3. ;

double Fearful::calculateNewDirection(Bestiole& bestiole, const std::vector<Bestiole>& neighbors){
    if (neighbors.empty())
        return bestiole.getOrientation();
    double moyenneX = 0.0;
    double moyenneY = 0.0;

    // Calcul du barycentre des neighbors proches
    double nouvelleOrientation;
    for (const auto& neighbor : neighbors) {
        moyenneX += neighbor.getCoordx();
        moyenneY += neighbor.getCoordy();
    }
    moyenneX /= neighbors.size();
    moyenneY /= neighbors.size();

    // Direction à adopter pour aller à l'opposé du barycentre
    double dx = moyenneX - bestiole.getCoordx();
    double dy = moyenneY - bestiole.getCoordy();

    if (dy > 0) {
        nouvelleOrientation = M_PI / 2 - atan2(dx, dy);  // atan2(x, y) fait arctan(x/y)
    } else if (dy < 0) {
        nouvelleOrientation = M_PI / 2 + atan2(dx, dy);
    } else {
        if (dx > 0) {
            nouvelleOrientation = 0;
        } else if (dx < 0) {
            nouvelleOrientation = M_PI;
        } else {
            // Si dx et dy sont tous deux nuls, on garde l'orientation actuelle
            nouvelleOrientation = bestiole.getOrientation();
        }
    }
    return nouvelleOrientation;
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

