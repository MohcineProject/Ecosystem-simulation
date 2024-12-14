
#include "CapteurS.h"

#include <iostream>


// Constructor for the sound sensor (CapteurS)
CapteurS::CapteurS(float capSMax, float capSMin, float distMax, float distMin) {
    // Generate a random float in [0, 1]
    float randomDraw = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    // Scale to the range [distMin, distMax] and cast to int if needed
    this->r = distMin + randomDraw * (distMax - distMin);

    // Generate another random float in [0, 1]
    float randomDraw2 = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    // Scale to the range [capSMin, capSMax]
    this->cap_detec = capSMin + randomDraw2 * (capSMax - capSMin);
}
// Default destructor for CapteurS
CapteurS::~CapteurS() = default;

/**
 * @brief Updates the set of detected "Bestiole" objects based on their positions and the sound detection radius.
 *
 * @param coordvector A vector of pairs representing the squared distances and angles of other entities.
 * @param k The index of the current "Bestiole" being updated.
 * @param listeBestioles A vector containing all "Bestiole" objects.
 * @return A set of pointers to "Bestiole" objects detected within the sound sensor's range.
 */
std::set<Bestiole *> CapteurS::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        // Check if the "Bestiole" is within the sound detection range and is not the current one
        if (coordvector[i].first < r * r * cap_detec * cap_detec && i != k) {
            if (listeBestioles[i].detectionCapability <= cap_detec) {
                bestioles.insert(&listeBestioles[i]); // Add detected "Bestiole" to the set
            }
        }
    }
    return bestioles;
}
