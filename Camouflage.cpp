#include "Camouflage.h"



Camouflage::Camouflage(float camouflage_capacity)
    : camouflage_capacity(camouflage_capacity) {}


double Camouflage::getSpeedFactor() const {
    return 1.0;
}

float Camouflage::getDetectionModifier() const {
    return camouflage_capacity;
}

float Camouflage::getResistanceModifier() const {
    return 1.0;
}

std::string Camouflage::getType() const {
    return "Camouflage";
}


