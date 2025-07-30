#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H
#include <string>


class Bestiole;

/**
 *@class Accessoire
 * @brief Abstract base class for accessories that can be added to a Bestiole.
 * Accessories can modify speed, detection capabilities, and resistance of a Bestiole.
 */
class Accessoire {
public:

    /**
     * @brief Gets the speed factor modifier provided by the accessory.
     * Pure virtual function, must be implemented by derived classes.
     */
    virtual double getSpeedFactor() const = 0;

    /**
     * @brief Gets the detection modifier provided by the accessory.
     * Default implementation returns 1.0 (no modification).
     */
    virtual float getDetectionModifier() const { return 1.0; }

    /**
    * @brief Gets the resistance modifier provided by the accessory.
    * Default implementation returns 1.0 (no modification).
    */
    virtual float getResistanceModifier() const { return 1.0; }

    /**
    * @brief Gets the type of the accessory as a string.
    * Pure virtual function, must be implemented by derived classes.
    */
    virtual std::string getType() const = 0;
    /**
    * @brief Virtual destructor to ensure proper cleanup of derived classes.
    */
    virtual ~Accessoire() = default;
};

#endif //ACCESSOIRE_H