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
   Aquarium       ecosystem( 1020, 720, 30 );
   ecosystem.createBestioles(0.1, 0.1, 0.2, 0.5, 0.1, 30);
   ecosystem.run();

   return 0;

}