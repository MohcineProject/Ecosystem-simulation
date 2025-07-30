#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "Behaviour.h"

/**
 * @class Kamikaze
 * @brief Represents the "kamikaze" behaviour for a Bestiole.
 *
 * The Kamikaze behavior causes a Bestiole to move towards
 * the closest neighboring Bestiole to make a collision.
 */
class Kamikaze : public Behaviour {

    /**
     * @brief Calculates the new direction for the Kamikaze Bestiole.
     *
     * Determines the direction for the kamikaze bestiole to take in order to make a collision with the closest neighbor.
     *
     * @param closestBestiolePtr A pointer to the closest neighboring Bestiole.
     * @return The new direction orientation.
     */
    double calculateNewDirection(const Bestiole* closestBestiolePtr);

public:
    /**
     * @brief Constructor for the Kamikaze class.
     *
     * Initializes a Kamikaze behaviour for a given Bestiole.
     *
     * @param bestiole A pointer to the Bestiole using this behavior.
     */
    Kamikaze(Bestiole* bestiole);

    /**
     * @brief Default destructor for the Kamikaze class.
     */
    ~Kamikaze() = default;

    /**
     * @brief Executes the Kamikaze behaviour.
     *
     * This method identifies the closest neighboring Bestiole and adjusts the
     * direction of the Kamikaze Bestiole to move towards it.
     *
     * @param neighbors A set of pointers to neighboring Bestioles.
     */
    void doBehaviour(std::set<Bestiole*>& neighbors) override;
};

#endif // KAMIKAZE_H
