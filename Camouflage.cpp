#include "Camouflage.h"



Camouflage::Camouflage(float camouflage_capacity)
    : camouflage_capacity(camouflage_capacity) {}


/**
 * Returns the speed factor modifier for Camouflage (no modification, returns 1.0).
 */
double Camouflage::getSpeedFactor() const {
    return 1.0;
}

/**
 * Returns the detection modifier based on the camouflage capacity.
 */
float Camouflage::getDetectionModifier() const {
    return camouflage_capacity;
}

/**
 * Returns the resistance modifier for Camouflage (no modification, returns 1.0).
 */
float Camouflage::getResistanceModifier() const {
    return 1.0;
}


/**
 * Returns the type of the accessory as "Camouflage".
 */
std::string Camouflage::getType() const {
    return "Camouflage";
}


