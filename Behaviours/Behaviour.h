//
// Created by mouha1505 on 28/11/24.
//

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <cmath>
#include <set>
#include <string>


class Bestiole;

class Behaviour
{
protected:
    std::string type;
    public:
        Bestiole *bestiole = nullptr; // a pointer to the bestiole we want to apply the behaviour
        virtual ~Behaviour() = default;
        virtual void doBehaviour(std::set<Bestiole*>& neighbors) = 0; // method to be override in child class
        Bestiole* closestBestiole(const std::set<Bestiole*>& neighbors);  // method to compute the closest bestiole
        virtual std::string getType() = 0;
};

#endif //BEHAVIOUR_H
