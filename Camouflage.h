#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "Accessoire.h"

class Bestiole;
/**
 * @class Camouflage
 * @brief Represents the Camouflage accessory for a Bestiole.
 * Modifies the detection capabilities based on its camouflage capacity.
 */
class Camouflage : public Accessoire {
private:
   /**
    * @brief Capacity of camouflage, affects detection modifier.
    */
   float camouflage_capacity;

public:
   /**
    * @brief Constructs the camouflage accessory with the passed value of camouflage capacity
    * @param camouflage_capacity a
    */
   explicit Camouflage(float camouflage_capacity);
    /**
 * @brief Returns the speed factor modifier for Camouflage (no modification, returns 1.0).
 */
    double getSpeedFactor() const override;
    /**
 * @brief Returns the detection modifier based on the camouflage capacity.
 */
    float getDetectionModifier() const override;
    /**
 * @brief the resistance modifier for Camouflage (no modification, returns 1.0).
 * @return the resistance modifier of the camouflage
 */
    float getResistanceModifier() const override;
    /**
 * @brief Returns the type of the accessory as "Camouflage".
 */
    std::string getType() const override;
};

#endif // CAMOUFLAGE_H