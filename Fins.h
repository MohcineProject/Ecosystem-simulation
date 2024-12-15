#ifndef FINS_H
#define FINS_H
#include "Accessoire.h"
#include <string>

/**
 * Represents the Fins accessory for a Bestiole.
 * Modifies the speed of a Bestiole based on a multiplier.
 */
class Fins : public Accessoire {
private:
    /**
     * Multiplier to increase the speed of the Bestiole.
     */
    double  speedMultiplier;

public:
    /**
     * @brief Construct a fins accessory by passing the speed multiplier factor.
     * @param multiplier a factor to multiply the speed
     */
    explicit Fins(double multiplier);
    /**
 * Returns the speed factor modifier for Fins based on the multiplier.
 */
    double getSpeedFactor() const override ;
    /**
 * Returns the type of the accessory as "Fins".
 */
    std :: string getType() const override ;
    /**
 * Sets a new speed multiplier for the Fins accessory.
 */
    void setSpeedMultiplier(double multiplier) ;
};


#endif


