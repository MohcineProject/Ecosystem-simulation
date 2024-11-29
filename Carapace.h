//
// Created by mouad on 26/11/2024.
//

#ifndef CARAPACE_H
#define CARAPACE_H
#include "Accessoire.h"
class Carapace : public Accessoire {
public:
    Carapace(double omega, double mu) : omega_(omega), mu_(mu) {}
    void applyEffect() override {
        // Apply collision resistance and speed reduction
    }
    std::string getType() const override { return "Carapace"; }
private:
    double omega_, mu_;
};







#endif //CARAPACE_H
