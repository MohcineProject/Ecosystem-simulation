//
// Created by mouha1505 on 28/11/24.
//

#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <vector>

class Bestiole;

class Behaviour
{
public:
    virtual ~Behaviour() = default;
    virtual void doBehaviour(Bestiole& me, const std::vector<Bestiole>& neighbors) = 0;
};

#endif //BEHAVIOUR_H
