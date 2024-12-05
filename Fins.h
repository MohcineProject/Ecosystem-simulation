#ifndef FINS_H
#define FINS_H
#include "Accessoire.h"
#include <string>

class Fins : public Accessoire {
private:
    double  speedMultiplier;

public:
    Fins(double multiplier);
    ~Fins() {}
    double getSpeedFactor() const override ;
    std :: string getType() const override ;
    void setSpeedMultiplier(double multiplier) ;
};


#endif


