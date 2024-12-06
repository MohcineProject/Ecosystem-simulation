#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H
#include <string>


class Bestiole;

class Accessoire {
public:

    virtual double getSpeedFactor() const = 0; // Pure virtual
    virtual float getDetectionModifier() const { return 1.0; }
    virtual float getResistanceModifier() const { return 1.0; }
    virtual std::string getType() const = 0;  // Pure virtual
    virtual ~Accessoire() = default;
};

#endif //ACCESSOIRE_H
