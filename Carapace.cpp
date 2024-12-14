#include "Carapace.h"



/**
 * Implementation of the Carapace accessory.
 * Increases resistance and detectability, while reducing speed.
 */
Carapace::Carapace(float cap_detect, float resistance_factor, float speed_factor)
    : cap_detect(cap_detect), resistance_factor(resistance_factor), speed_factor(speed_factor) {}

Carapace::~Carapace() {}


/**
 * Returns the speed factor modifier for Carapace, which decreases the speed.
 */
double Carapace::getSpeedFactor() const {
    return speed_factor;
}


/**
 * Returns the detectability modifier for Carapace.
 */
float Carapace::getCapDetect() const {
    return cap_detect;
}


/**
 * Returns the resistance modifier for Carapace.
 */
float Carapace::getResistanceFactor() const {
    return resistance_factor;
}


/**
 * Returns the type of the accessory as "Carapace".
 */
std::string Carapace::getType() const {
    return "Carapace";
}


