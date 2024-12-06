
#include "Fins.h"

Fins::Fins(double multiplier) : speedMultiplier(multiplier) {}


double Fins::getSpeedFactor() const {
    return speedMultiplier;
}

std::string Fins::getType() const {
    return "Fins";
}

void Fins::setSpeedMultiplier(double multiplier) {
    speedMultiplier = multiplier;
}
