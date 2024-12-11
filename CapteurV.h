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
    int r;
    int angle;
    float cap_detec;

    public:
    CapteurV(float capVMax, float capVMin, float AngleMax, float AngleMin, float distMax, float distMin);
    ~CapteurV();
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);
    int getAngle() const {
        return angle;
    }
    float getR() const {
        return r;
    }

    int getTheta() const {
        return angle;
    }

};



#endif //CAPTEURV_H
