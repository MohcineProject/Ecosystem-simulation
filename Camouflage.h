#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "Accessoire.h"

class Bestiole;


/**
 * Represents the Camouflage accessory for a Bestiole.
 * Modifies the detection capabilities based on its camouflage capacity.
 */
class Camouflage : public Accessoire {
private:
    float camouflage_capacity; ///< Capacity of camouflage, affects detection modifier.


public:
    Camouflage(float camouflage_capacity);
    ~Camouflage() override;
    double getSpeedFactor() const override;
    float getDetectionModifier() const override;
    float getResistanceModifier() const override;
    std::string getType() const override;
};

#endif // CAMOUFLAGE_H