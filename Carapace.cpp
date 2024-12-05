#include "Carapace.h"

Carapace::Carapace(float cap_detect, float resistance_factor, float speed_factor)
    : cap_detect(cap_detect), resistance_factor(resistance_factor), speed_factor(speed_factor) {}

Carapace::~Carapace() {}

double Carapace::getSpeedFactor() const {
    return speed_factor;
}

float Carapace::getCapDetect() const {
    return cap_detect;
}

float Carapace::getResistanceFactor() const {
    return resistance_factor;
}

std::string Carapace::getType() const {
    return "Carapace";
}


