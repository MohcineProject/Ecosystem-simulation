//
// Created by zahdi on 25/05/2025.
//

#ifndef BESTIOLEFACTORY_H
#define BESTIOLEFACTORY_H

#include "../Aquarium/Aquarium.h"
#include "Bestiole.h"

class BestioleFactory {
        /**
         * The singleton instance of the BestioleFactory.
         */
        static BestioleFactory* bestioleFactory  ;

        /**
         * The aquarium instance used to retrieve the environement parameters for the creation of bestioles.
         */
        const Aquarium* aquarium;

        /**
         * Constructor of the bestiole factory.
         * @param aquarium the Aquarium instance used by the factory to get parameters for the creation of bestioles.
         */
        explicit BestioleFactory(const Aquarium* aquarium);

        /**
         * A function used to equip the bestiole wit
         * @param b
         */
        void equip_bestiole(Bestiole* b) const;

public:
        /**
         * A static function to retrieve the singleton instance of the bestiole factory.
         * @param aquarium the Aquarium instance used to initialize the factory.
         * @return the bestiole factory singleton.
         */
        static BestioleFactory* getBestioleFactory(const Aquarium* aquarium) ;

        /**
         * The function used to create a factory.
         * @param bestiole_type The type of the bestiole to be created.
         * @return a pointer to the newly created bestiole.
         */
        Bestiole* createBestiole(const string& bestiole_type) const;


};



#endif
