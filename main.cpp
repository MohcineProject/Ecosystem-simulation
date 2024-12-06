#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Accessoire.h"
#include "Fins.h"
#include "Carapace.h"
#include "Camouflage.h"

#include <iostream>
#include <memory>

using namespace std;

int main() {
    // Create an Aquarium with specified dimensions and frame rate
    Aquarium ecosysteme(640, 480, 30);

    // Create Bestioles with different accessories
    Bestiole b1(5.0); // Without accessories
    b1.setBehaviour("Fearful");
    b1.doBehavour();

    Bestiole b2(5.0); // With fins
    shared_ptr<Accessoire> finsPtr = make_shared<Fins>(1.5);
    b2.addAccessory(finsPtr);

    Bestiole b3(5.0); // With carapace
    shared_ptr<Accessoire> carapacePtr = make_shared<Carapace>(1.2, 1.5, 0.8);
    b3.addAccessory(carapacePtr);

    Bestiole b4(5.0); // With camouflage
    shared_ptr<Accessoire> camouflagePtr = make_shared<Camouflage>(0.8);
    b4.addAccessory(camouflagePtr);

    Bestiole b5(5.0); // With carapace and camouflage
    b5.addAccessory(carapacePtr);
    b5.addAccessory(camouflagePtr);

    // Add the Bestioles to the Milieu
    Milieu& milieu = ecosysteme.getMilieu();
    milieu.addMember(b1);
    milieu.addMember(b2);
    milieu.addMember(b3);
    milieu.addMember(b4);
    milieu.addMember(b5);


    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;
    cout << b5 << endl;


    // Run the simulation
    ecosysteme.run();

   return 0;
}