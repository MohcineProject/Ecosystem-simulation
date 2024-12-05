
#include "CapteurV.h"

#include <iostream>

CapteurV::CapteurV() {

}


CapteurV::~CapteurV() = default;


std::set<Bestiole *> CapteurV::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        if (i != k && - angle < coordvector[i].second < angle && coordvector[i].first < r * r) {
            std::cout << k << "  sees    " << i << std::endl;
            bestioles.insert(&listeBestioles[i]);
        }
    }
    return bestioles;
}

