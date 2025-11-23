//
// Created by zahdi on 25/05/2025.
//

#include "BestioleFactory.h"
#include "Accessories/Fins.h"
#include "Accessories/Carapace.h"



BestioleFactory* BestioleFactory::bestioleFactory = nullptr;

BestioleFactory::BestioleFactory(const Aquarium* aquarium):  aquarium(aquarium) {
}

BestioleFactory* BestioleFactory::getBestioleFactory(const Aquarium* aquarium) {
    // Use singleton pattern to ensure the objects only use one factory
    if (bestioleFactory == nullptr) {
        bestioleFactory = new BestioleFactory(aquarium) ;
        return bestioleFactory ;
    }
    else {
        return bestioleFactory;
    }
}

Bestiole *BestioleFactory::createBestiole( const string& bestiole_type) const {
    const auto new_bestiole = new Bestiole(10) ;
    new_bestiole->setBehaviour(bestiole_type) ;
    equip_bestiole(new_bestiole);
    return new_bestiole;
}


void BestioleFactory::equip_bestiole(Bestiole* b) const {

    // Specifying its detection capability
    float detectionCapabilityDraw = static_cast<float>(std::rand()) / RAND_MAX;
    float detectionCapability = aquarium->get_camouflage_min() + detectionCapabilityDraw * (aquarium->get_camouflage_max() - aquarium->get_camouflage_min());
    b->detectionCapability = detectionCapability;

    // Define a threshold for attaching captors and accessories randomly to bestioles
    constexpr float randomizer = 0.3;

    // Assigning accessories and captors randomly

    // Assigning the sound captor
    const float captorSDraw = static_cast<float>(std::rand()) / RAND_MAX;
    if (captorSDraw <= randomizer) {
        b->attachCaptorS(
            aquarium->get_detec_h_max() , aquarium->get_detec_h_min(),
            aquarium->get_distance_hearing_min(), aquarium->get_distance_hearing_max()
        );
    }

    // Assigning the vision captor
    const float captorVDraw = static_cast<float>(std::rand()) / RAND_MAX;
    if (captorVDraw <= randomizer) {
        b->attachCaptorV(
            aquarium->get_detec_v_max(), aquarium->get_detec_h_min(),
            aquarium->get_angle_vision_max(),aquarium->get_angle_vision_min(),
            aquarium->get_distance_vision_max(), aquarium->get_distance_vision_min()
        );
    }

    // Assigning fins
    const float finDraw = static_cast<float>(std::rand()) / RAND_MAX;
    if (finDraw <= randomizer) {
        const float finMultDraw = static_cast<float>(std::rand()) / RAND_MAX;
        std::shared_ptr<Accessoire> f = std::make_shared<Fins>(
            1 + finMultDraw * (aquarium->get_mult_speed_max() - 1 )
        );
        b->addAccessory(f);
    }

    // Assigning shell
    const float shellDraw = static_cast<float>(std::rand()) / RAND_MAX;
    if (shellDraw <= randomizer) {
        const float shellRedDraw = static_cast<float>(std::rand()) / RAND_MAX;
        float shellRed = 1 + shellRedDraw * (aquarium->get_red_speed_max() - 1);
        const float shellResDraw = static_cast<float>(std::rand()) / RAND_MAX;
        float shellRes = 1 + shellResDraw * (aquarium->get_resistance_max() - 1);
        const shared_ptr<Accessoire> s = make_shared<Carapace>(1, shellRes, shellRed);
        b->addAccessory(s);
        b->detectionCapability *= 0.5;
    }

}
