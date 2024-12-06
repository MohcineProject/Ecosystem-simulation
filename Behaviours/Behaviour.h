//
// Created by mouha1505 on 28/11/24.
//

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <cmath>
#include <set>


class Bestiole;

class Behaviour
{
    protected:
    Bestiole *bestiole = nullptr;

    public:
        virtual ~Behaviour() = default;
        virtual void doBehaviour(std::set<Bestiole*>& neighbors) = 0;
        Bestiole* closestBestiole(const std::set<Bestiole*>& neighbors);
};

#endif //BEHAVIOUR_H
