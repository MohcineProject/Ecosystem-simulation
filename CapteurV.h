//
// Created by pc on 05/12/2024.
//

#ifndef CAPTEURV_H
#define CAPTEURV_H

#include <vector>
#include <set>

#include "Bestiole.h"

class Bestiole;


/**
 * @class CapteurV
 * @brief Represents the vision captor of the bestioles.
 * It provides a vision field where bestioles can detect others.
 *
 * The CapteurV class allows a Bestiole to detect other Bestioles within its
 * vision field. This class manages the detection radius, angle, and the
 * detection capability factor that controls how well a Bestiole can perceive others.
 */
class CapteurV {
private:
    int r;            ///< Detection radius
    int angle;        ///< Detection angle
    float cap_detec;  ///< Detection capability factor

public:
    /**
     * @brief Constructor that takes arguments related to detection range (radius, angle, and detection capability factor).
     *
     * This constructor initializes the vision captor with a maximum and minimum detection capability,
     * angle, and distance.
     *
     * @param capVMax Maximum detection capability.
     * @param capVMin Minimum detection capability.
     * @param AngleMax Maximum detection angle.
     * @param AngleMin Minimum detection angle.
     * @param distMax Maximum detection distance.
     * @param distMin Minimum detection distance.
     */
    CapteurV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin);

    /**
     * @brief Destructor for CapteurV.
     *
     */
    ~CapteurV();

    /**
     * @brief Updates the set of detected "Bestiole" objects within the visual sensor's field.
     *
     * This method computes which Bestioles are within the sensor's vision field,
     * based on their squared distance and angle, and returns a set of detected Bestioles.
     *
     * @param coordvector A vector of pairs representing the squared distances and angles of other entities.
     * @param i The index of the current "Bestiole" being updated.
     * @param listeBestioles A vector containing all "Bestiole" objects.
     * @return A set of pointers to "Bestiole" objects detected within the sensor's range.
     */
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);




    /**
     * @brief Getter for the detection radius.
     *
     * @return The detection radius of the vision sensor.
     */
    float getR() const {
        return r;
    }

    /**
     * @brief Getter for the detection angle.
     *
     * @return The detection angle of the vision sensor.
     */
    int getTheta() const {
        return angle;
    }
};

#endif //CAPTEURV_H
