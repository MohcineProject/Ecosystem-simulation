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
    double  speedMultiplier; ///< Multiplier to increase the speed of the Bestiole.

public:
    Fins(double multiplier);
    ~Fins() {}
    double getSpeedFactor() const override ;
    std :: string getType() const override ;
    void setSpeedMultiplier(double multiplier) ;
};


#endif


