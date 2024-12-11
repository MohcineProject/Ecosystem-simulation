
#include "CapteurS.h"

#include <iostream>

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

CapteurS::~CapteurS() = default;

std::set<Bestiole *> CapteurS::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        if (coordvector[i].first < r * r * cap_detec * cap_detec && i != k) {
            if (listeBestioles[i].detectionCapability <= cap_detec) {
                bestioles.insert(&listeBestioles[i]);
            }
        }
    }
    return bestioles;
}
