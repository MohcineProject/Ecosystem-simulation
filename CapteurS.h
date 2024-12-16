#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "Bestiole.h"
#include <vector>
#include <set>

class Bestiole;


/**
 * @class CapteurS
 * Sensor class for detecting nearby Bestiole objects using sound (CapteurS).
 * Implements a detection range and adds detected Bestiole objects to a set.
 */
class CapteurS {
private:
    int r; ///< Detection range.
    float cap_detec; ///< Detection capability factor.


public:
    /**
     * @brief Default constructor.
     */
    CapteurS(float capSMax, float capSMin, float distMax, float distMin);

    /**
     * @brief Default destructor.
     */
    ~CapteurS() ;

    /**
     * @brief Updates the sensor state by checking for nearby Bestiole objects based on sound detection.
     *
     * @param coordvector A vector of coordinates representing the positions of other Bestiole objects.
     * @param i Index of the current Bestiole object.
     * @param listeBestioles List of all Bestiole objects.
     * @return A set of detected Bestiole objects within the sound detection range.
     */
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);
    int getR() const {
        return r;
    }
};

#endif // CAPTEURS_H