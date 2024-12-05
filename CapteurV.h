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
    int r = 80;
    int angle = 20;
    float cap_detec = 1;

    public:
    CapteurV();
    ~CapteurV();
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);

};



#endif //CAPTEURV_H
