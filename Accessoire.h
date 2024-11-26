//
// Created by mouad on 26/11/2024.
//

#ifndef ACCESSOIRE_H
#define ACCESSOIRE_H
#include <string>

class Accessoire {
public:
    virtual ~Accessoire() = default;
    virtual void applyEffect() = 0;
    virtual std::string getType() const = 0;
};

#endif //ACCESSOIRE_H
