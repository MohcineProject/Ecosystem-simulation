//
// Created by mouad on 26/11/2024.
//

#ifndef FINS_H
#define FINS_H
#include "Accessoire.h"

class Fins : public Accessoire {
public:
    Fins(double speedFactor) : speedFactor_(speedFactor) {}
    void applyEffect() override {
        // Apply speed increase
    }
    std::string getType() const override { return "Fins"; }
private:
    double speedFactor_;
};

#endif

#endif //FINS_H
