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
    b1.setBehaviour("Multiple");

    //Carapace *c = new Carapace(1,1,1);
    //Fins *f = new Fins(2);
    Bestiole b2(5.0);
    b2.setBehaviour("Cautious");

    //b2.addAccessory(shared_ptr<Accessoire>(c));
    //b2.addAccessory(shared_ptr<Accessoire>(f));

    Bestiole b3(5.0);
    b3.setBehaviour("Fearful");
    Bestiole b4(5.0);
    b4.setBehaviour("Fearful");

    Bestiole b5(5.0);
    b5.setBehaviour("Kamikaze");

    Bestiole b6(5.0);
    b6.setBehaviour("Gregaire");
    // Add the Bestioles to the Milieu
    Milieu& milieu = ecosysteme.getMilieu();
    milieu.addMember(b1);

    milieu.addMember(b2);

    milieu.addMember(b3);
    milieu.addMember(b4);
    milieu.addMember(b5);
    milieu.addMember(b6);

    cout << b1 << endl;

    cout << b2 << endl;

    cout << b3 << endl;
    cout << b4 << endl;
    cout << b5 << endl;
    cout << b6 << endl;

    // Run the simulation
    ecosysteme.run();
    //delete c;
    //delete f;

   return 0;
}