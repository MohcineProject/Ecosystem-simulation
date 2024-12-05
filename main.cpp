#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Test/GregaireTest.h"

using namespace std;


int main()
{
    GregaireTest test;
    test.testGregaire_NoNeighbors();
    test.testGregaire_WithNeighbors();

    return 0;

}
