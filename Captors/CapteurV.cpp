
#include "CapteurV.h"

#include <iostream>

// Constructor for the visual sensor (CapteurV)
CapteurV::CapteurV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin) {
    float randomDraw = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    float rd = distMin + randomDraw * (distMax - distMin);
    this->r = rd;
    float randomDraw2 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    // Scale to the range [capVMin, capVMax]
    this->cap_detec = capVMin + randomDraw2 * (capVMax - capVMin);

    // Generate another random float in [0, 1]
    float randomDraw3 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    // Scale to the range [AngleMin, AngleMax], converting to an integer if necessary
    this->angle = static_cast<int>(AngleMin + randomDraw3 * (AngleMax - AngleMin));

}

// Default destructor for CapteurV
CapteurV::~CapteurV() = default;

/**
 * @brief Updates the set of detected "Bestiole" objects based on their positions and the visual detection field.
 *
 * @param coordvector A vector of pairs representing the squared distances and angles of other entities.
 * @param k The index of the current "Bestiole" being updated.
 * @param listeBestioles A vector containing all "Bestiole" objects.
 * @return A set of pointers to "Bestiole" objects detected within the visual sensor's field of view.
 */
std::set<Bestiole *> CapteurV::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        // Check if the "Bestiole" is within the visual detection field (angle and radius) and is not the current one
        if (i != k && - angle < coordvector[i].second < angle && coordvector[i].first < r * r) {
            if (listeBestioles[i].detectionCapability <= cap_detec) {
                bestioles.insert(&listeBestioles[i]);
            }
        }
    }
    return bestioles;
}