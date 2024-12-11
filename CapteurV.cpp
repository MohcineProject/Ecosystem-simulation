
#include "CapteurV.h"

#include <iostream>

CapteurV::CapteurV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin) {
    int randomDraw = floor(std::rand() / RAND_MAX);
    this->r = distMin + randomDraw * (distMax - distMin);
    float randomDraw2 = static_cast<float>(std::rand() / RAND_MAX);
    this->cap_detec = capVMin + randomDraw2 * (capVMax - capVMin);
    int randomDraw3 = floor(std::rand() / RAND_MAX);
    this->angle = AngleMin + randomDraw3 * (AngleMax - AngleMin);

}


CapteurV::~CapteurV() = default;


std::set<Bestiole *> CapteurV::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        if (i != k && - angle < coordvector[i].second < angle && coordvector[i].first < r * r) {
            //std::cout << k << "  sees    " << i << std::endl;
            bestioles.insert(&listeBestioles[i]);
        }
    }
    return bestioles;
}

