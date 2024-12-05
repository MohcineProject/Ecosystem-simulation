
#include "Bestiole.h"
#include "Fins.h"
#include "Carapace.h"
#include <memory>
#include "Camouflage.h"


int main() {
    Bestiole b1(5.0); // Without accessories
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

    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;
    cout << b5 << endl;

    return 0;
}



/*int main() {
    Bestiole b1(5.0); // Without accessories
    Bestiole b2(5.0); // With fins
    shared_ptr<Accessoire> finsPtr = make_shared<Fins>(1.5);
    b2.addAccessory(finsPtr);

    Bestiole b3(5.0); // With carapace
    shared_ptr<Accessoire> carapacePtr = make_shared<Carapace>(1.2, 1.5, 0.8);
    b3.addAccessory(carapacePtr);

    Bestiole b4(5.0); // With both fins and carapace
    b4.addAccessory(finsPtr);
    b4.addAccessory(carapacePtr);

    cout << b1 << endl;
    cout << b2 << endl;
    cout << b3 << endl;
    cout << b4 << endl;

    return 0;
}*/
