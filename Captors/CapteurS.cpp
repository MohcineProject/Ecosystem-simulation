
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