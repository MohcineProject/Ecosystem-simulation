//
// Created by pc on 05/12/2024.
//

#ifndef CAPTEURV_H
#define CAPTEURV_H

#include <vector>
#include <memory>
#include <set>

#include "Bestiole.h"

class Bestiole;

class CapteurV {
private:
    int r;            // Detection radius
    int angle;        // Detection angle
    float cap_detec;  // Detection capability factor


public:

    // Constructor that takes arguments related to detection range (radius,angle and detaction capability factor)
    CapteurV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin);

    // Destructor
    ~CapteurV();

    /**
     * @brief Updates the set of detected "Bestiole" objects within the visual sensor's field.
     *
     * @param coordvector A vector of pairs representing the squared distances and angles of other entities.
     * @param i The index of the current "Bestiole" being updated.
     * @param listeBestioles A vector containing all "Bestiole" objects.
     * @return A set of pointers to "Bestiole" objects detected within the sensor's range.
     */
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);

    // Getter for the detection angle
    int getAngle() const {
        return angle;
    }
    // Getter for the detection radius
    float getR() const {
        return r;
    }

    // Getter for the Theta angle
    int getTheta() const {
        return angle;
    }

};



#endif //CAPTEURV_H