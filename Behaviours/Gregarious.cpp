//
// Created by mouha1505 on 28/11/24.
//

#include "Gregarious.h"
#include "../Bestiole.h"

/**
 * @brief Implements the "Gregarious" behavior for a "Bestiole".
 * This behavior aligns the "Bestiole's" direction with the average orientation of its neighbors.
 *
 * @param neighbors A set of pointers to neighboring "Bestiole" objects.
 */
void Gregarious::doBehaviour(std::set<Bestiole*>& neighbors){
    // If no neighbors are present, the behavior does nothing (no behaviour to execute)
    if (neighbors.empty())
        return;

    double avgDirection = 0.0; //Initialize the variable to calculate the average direcction.

    // Loop through each neighboring Bestiole and accumulate their orientations.
    for (const auto& neighbor : neighbors)
    {
        avgDirection += neighbor -> getOrientation();
    }
    avgDirection /= neighbors.size(); // Calculate the average direction by dividing the total by the number of neighbors.

    // Ensure the new direction is within the range [0, 2π] using modulo operation.
    double newDirection = fmod(avgDirection, 2*M_PI);

    // Set the orientation of the current Bestiole to the calculated average direction.
    bestiole->setOrientation(newDirection);

}

/**
 * @brief Constructor for the "Gregarious" behavior.
 *
 * @param bestiole Pointer to the "Bestiole" this behavior is associated with.
 */
Gregarious::Gregarious(Bestiole *bestiole) {
    this->bestiole = bestiole;
    this -> type = "Gregaire"; // Assign the behavior type
}
