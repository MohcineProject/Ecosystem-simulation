#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "Bestiole.h"
#include <vector>
#include <memory>
#include <set>

class Bestiole;

class CapteurS {
private:
    int r = 50;
    float cap_detec = 1;

public:
    CapteurS();
    ~CapteurS() ;
    std::set<Bestiole*> update(std::vector<std::pair<double, double>>& coordvector, int i, std::vector<Bestiole>& listeBestioles);
    int getR() const {
        return r;
    }
};

#endif // CAPTEURS_H
