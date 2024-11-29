//
// Created by mouad on 26/11/2024.
//

#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H
#include "Accessoire.h"

class Camouflage : public Accessoire {
public:
    Camouflage(double camouflageValue) : camouflageValue_(camouflageValue) {}
    void applyEffect() override {
        // Apply camouflage effect
    }
    std::string getType() const override { return "Camouflage"; }
private:
    double camouflageValue_;
};


#endif //CAMOUFLAGE_H
