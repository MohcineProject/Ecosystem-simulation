#include "Aquarium/Aquarium.h"
#include <iostream>

using namespace std;

int main() {
   Aquarium       ecosystem( 1020, 640, 30 );
   ecosystem.createBestioles(0.1, 0.1, 0.2, 0.2, 0.4, 100);
   ecosystem.run();

   return 0;

}


