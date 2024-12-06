#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "Accessoire.h"

class Bestiole;

class Camouflage : public Accessoire {
private:
    float camouflage_capacity;

public:
    Camouflage(float camouflage_capacity);
    ~Camouflage() override;
    double getSpeedFactor() const override;
    float getDetectionModifier() const override;
    float getResistanceModifier() const override;
    std::string getType() const override;
};

#endif // CAMOUFLAGE_H