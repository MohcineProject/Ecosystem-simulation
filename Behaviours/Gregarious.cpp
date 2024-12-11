//
// Created by mouha1505 on 28/11/24.
//

#include "Gregarious.h"
#include "../Bestiole.h"

void Gregarious::doBehaviour(std::set<Bestiole*>& neighbors){
    if (neighbors.empty())
        return;

    double avgDirection = 0.0;
    for (const auto& neighbor : neighbors)
    {
        avgDirection += neighbor -> getOrientation();
    }
    avgDirection /= neighbors.size();

    double newDirection = fmod(avgDirection, 2*M_PI);

    bestiole->setOrientation(newDirection);

}

Gregarious::Gregarious(Bestiole *bestiole) {
    this->bestiole = bestiole;
    this -> type = "Gregaire";
}
