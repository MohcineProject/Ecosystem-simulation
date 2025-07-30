//
// Created by mouha1505 on 29/11/24.
//

#ifndef CAUTIOUS_H
#define CAUTIOUS_H

#include "Behaviour.h"

class Bestiole;


/**
 * @brief Represents a behaviour where the Bestiole
 * acts cautiously, avoiding collision with other Bestioles.
 */
class Cautious : public Behaviour {
    /**
     * @brief Computes an orientation for the bestiole to get away from the closest detected bestiole.
     * @param closestBestiolePtr A pointer to the closest detected bestiole
     * @return The new direction that the bestiole should take
     */
    double calculateNewDirection(const Bestiole* closestBestiolePtr);

    public:
    /**
     * @brief Constructs a cautious behaviour by passing a pointer to the corresponding bestiole
     * @param bestiole 
     */
    Cautious(Bestiole* bestiole);

    /**
     * @brief Default constructor for the cautious behaviour
     */
    ~Cautious() = default;

    /**
     * @brief Overrides the doBehaviour method from the Behaviour base class. It assigns a new direction to the bestiole
     * @param neighbors 
     */
    void doBehaviour(std::set<Bestiole*> &neighbors) override;

};

#endif //CAUTIOUS_H
