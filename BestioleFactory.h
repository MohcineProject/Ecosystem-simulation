//
// Created by zahdi on 25/05/2025.
//

#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include "Aquarium.h"
#include "Bestiole.h"

class BestioleFactory {


        static BestioleFactory* bestioleFactory  ;
        const Aquarium* aquarium;

        explicit BestioleFactory(const Aquarium* aquarium);

public:
        static BestioleFactory* getBestioleFactory(const Aquarium* aquarium) ;
        Bestiole* createBestiole(const string& bestiole_type) const;
        void equip_bestiole(Bestiole* b) const;

};



#endif
