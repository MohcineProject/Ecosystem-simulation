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
    Carapace(float cap_detect, float resistance_factor, float speed_factor);
    ~Carapace() override;
    double getSpeedFactor() const override;
    std::string getType() const override;
    float getCapDetect() const;
    float getResistanceFactor() const;
};

#endif // CARAPACE_H