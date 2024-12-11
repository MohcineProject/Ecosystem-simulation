
#include "CapteurS.h"

#include <iostream>

CapteurS::CapteurS(float capSMax, float capSMin, float distMax, float distMin) {
    int randomDraw = static_cast<int>(std::rand() / RAND_MAX);
    this->r = distMin + randomDraw * (distMax - distMin);
    float randomDraw2 = static_cast<float>(std::rand() / RAND_MAX);
    this->cap_detec = capSMin + randomDraw2 * (capSMax - capSMin);
}

CapteurS::~CapteurS() = default;

std::set<Bestiole *> CapteurS::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        if (coordvector[i].first < r * r * cap_detec * cap_detec && i != k) {
            //std::cout << k << "  hears    " << i << std::endl;
            bestioles.insert(&listeBestioles[i]);
        }
    }
    return bestioles;
}
