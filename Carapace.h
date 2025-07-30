#ifndef CARAPACE_H
#define CARAPACE_H

#include "Accessoire.h"
class Bestiole;


/**
 * @class Carapace
 * @brief Represents the Carapace accessory for a Bestiole.
 *
 * The Carapace class modifies the characteristics of a Bestiole by adjusting
 * its detection, resistance, and speed properties.
 */
class Carapace : public Accessoire {
private:
    float cap_detect; ///< Increased detectability (reduction in detectability)
    float resistance_factor; ///< Resistance factor that enhances the Bestiole's resistance
    float speed_factor; ///< Speed factor that reduces the Bestiole's speed

public:
    /**
     * @brief Constructs a Carapace with the specified values.
     *
     * This constructor initializes the Carapace accessory with values that affect
     * detection, resistance, and speed attributes of the Bestiole.
     *
     * @param cap_detect A reducing coefficient to decrease the detection capacity of a Bestiole.
     * @param resistance_factor A factor to increase the Bestiole's resistance.
     * @param speed_factor A factor to reduce the Bestiole's speed.
     */
    Carapace(float cap_detect, float resistance_factor, float speed_factor);

    /**
     * @brief Returns the speed factor modifier for Carapace, which decreases the speed.
     *
     * @return The speed reduction factor of the Carapace.
     */
    double getSpeedFactor() const override;

    /**
     * @brief Returns the type of the accessory as "Carapace".
     *
     * @return The string "Carapace" representing the type of the accessory.
     */
    std::string getType() const override;

    /**
     * @brief Returns the detectability modifier for Carapace.
     *
     * @return The detectability modifier (reduction factor) for the Carapace.
     */
    float getCapDetect() const;

    /**
     * @brief Returns the resistance modifier for Carapace.
     *
     * @return The resistance modifier of the Carapace.
     */
    float getResistanceFactor() const;
};

#endif // CARAPACE_H
