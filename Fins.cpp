
#include "Fins.h"


/**
 * Implementation of the Fins accessory.
 * Increases the speed of a Bestiole based on a speed multiplier.
 */
Fins::Fins(double multiplier) : speedMultiplier(multiplier) {}

/**
 * Returns the speed factor modifier for Fins based on the multiplier.
 */
double Fins::getSpeedFactor() const {
    return speedMultiplier;
}

/**
 * Returns the type of the accessory as "Fins".
 */
std::string Fins::getType() const {
    return "Fins";
}

/**
 * Sets a new speed multiplier for the Fins accessory.
 */
void Fins::setSpeedMultiplier(double multiplier) {
    speedMultiplier = multiplier;
}


