//
// Created by mouha1505 on 28/11/24.
//

#include "Gregarious.h"
#include "../Bestiole.h"



void Gregarious::doBehaviour(std::set<Bestiole*>& neighbors){
    // If the no neighbor is detected return.
    if (neighbors.empty())
        return;

    // Calculate the average orientation of all neighbors
    double avgDirection = 0.0;
    for (const auto& neighbor : neighbors)
    {
        avgDirection += neighbor -> getOrientation();
    }
    avgDirection /= neighbors.size();

    // Calculate the modulus of the orientation and set it to the bestiole
    double newDirection = fmod(avgDirection, 2*M_PI);
    bestiole->setOrientation(newDirection);

}

Gregarious::Gregarious(Bestiole *bestiole) {
    this->bestiole = bestiole;
    this -> type = "Gregaire";
}
