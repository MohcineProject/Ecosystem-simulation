#ifndef CARAPACE_H
#define CARAPACE_H

#include "Accessoire.h"
class Bestiole;


/**
 * Represents the Carapace accessory for a Bestiole.
 * Modifies detection, resistance, and speed characteristics.
 */
class Carapace : public Accessoire {
private:
    float cap_detect; // Increased detectability
    float resistance_factor; // Increased resistance
    float speed_factor; // Decreased speed

public:
    /**
     * Construct a carapace with the specified values
     * @param cap_detect a reducing coefficient to decrease the capacity of detection of a bestiole
     * @param resistance_factor a resistance factor to increase a bestiole resistance
     * @param speed_factor a factor to reduce a bestiole speed
     */
    Carapace(float cap_detect, float resistance_factor, float speed_factor);

    /**
     * Returns the speed factor modifier for Carapace, which decreases the speed.
     */
    double getSpeedFactor() const override;
    /**
 * Returns the type of the accessory as "Carapace".
 */
    std::string getType() const override;
    /**
 * Returns the detectability modifier for Carapace.
 */
    float getCapDetect() const;

    /**
     * Returns the resistance modifier for Carapace.
     */
    float getResistanceFactor() const;
};

#endif // CARAPACE_H