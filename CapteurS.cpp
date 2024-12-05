
#include "CapteurS.h"

#include <iostream>

CapteurS::CapteurS() {
}

CapteurS::~CapteurS() = default;

std::set<Bestiole *> CapteurS::update(std::vector<std::pair<double, double> > &coordvector, int k,
                                      std::vector<Bestiole> &listeBestioles) {
    std::set<Bestiole *> bestioles;
    for (int i = 0; i < coordvector.size(); i++) {
        if (coordvector[i].first < r * r * cap_detec * cap_detec && i != k) {
            std::cout << k << "  hears    " << i << std::endl;
            bestioles.insert(&listeBestioles[i]);
        }
    }
    return bestioles;
}
