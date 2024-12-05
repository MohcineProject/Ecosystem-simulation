#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"

#include <iostream>

#include "Test/FearfulTest.h"

using namespace std;


int main()
{
    FearfulTest test;
    test.testDoBehaviour_NoNeighbors();
    test.testDoBehaviour_WithNeighborsAboveDensity();
    test.testDoBehaviour_WithNeighborsBelowDensity();

    return 0;

}