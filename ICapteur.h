#ifndef ICAPTEUR_H
#define ICAPTEUR_H

#include <vector>

class Bestiole;


/**
 * Abstract interface for sensors ("Capteurs") used by Bestiole to interact with its environment.
 * Derived classes must implement the update method to define specific behavior.
 */
class ICapteur {
private:
    std::vector<Bestiole*> nearbyObjects; ///< Stores the nearby Bestiole objects detected by the sensor.
public:

    /**
     * Default constructor.
     */
    ICapteur() = default;

    /**
     * Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~ICapteur() = default;

    /**
     * Pure virtual function to update the sensor's state based on detected objects.
     * Derived classes must provide an implementation.
     *
     * @param coordvector A vector of coordinates representing the positions of other Bestiole objects.
     */
    virtual void update(std::vector<std::pair<double, double>>& coordvector) = 0;
};

#endif // ICAPTEUR_H
