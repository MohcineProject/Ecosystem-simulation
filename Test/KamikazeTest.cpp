//
// Created by mouha1505 on 05/12/24.
//
#include <iostream>
#include <cmath>
#include <set>
#include "Behaviours/Kamikaze.h"
#include "../Bestiole.h"
#include "KamikazeTest.h"

// Helper function to create a Bestiole

void KamikazeTest::testDoBehaviour_NoNeighbors() {
    Kamikaze kamikaze;
    Bestiole testBestiole = createBestiole(0.0, 0.0, M_PI / 4); // Initial orientation: 45 degrees

    // Test with no neighbors
    std::set<Bestiole> neighbors;
    kamikaze.doBehaviour(testBestiole, neighbors);

    if (testBestiole.getOrientation() == M_PI / 4) {
        std::cout << "kamikaze : test doBehaviour with No Neighbors PASSED\n";
    } else {
        std::cout << "kamikaze : test doBehaviour with No Neighbors FAILED\n";
    }
}

void KamikazeTest::testDoBehaviour_WithNeighbors() {
    Kamikaze kamikaze;
    Bestiole testBestiole = createBestiole(0.0, 0.0, M_PI / 4); // Initial orientation: 45 degrees
    Bestiole neighbor1 = createBestiole(1.0, 1.0, 0.0);         // Positioned at (1,1)
    Bestiole neighbor2 = createBestiole(2.0, 2.0, 0.0);         // Positioned at (2,2)

    // Test with neighbors
    std::set<Bestiole> neighbors = {neighbor1, neighbor2};
    kamikaze.doBehaviour(testBestiole, neighbors);

    // Compute expected direction
    double dx = neighbor1.getCoordx() - testBestiole.getCoordx();
    double dy = neighbor1.getCoordy() - testBestiole.getCoordy();
    double expectedOrientation = M_PI / 2 + atan2(dy, dx) + M_PI; // Reverse direction

    if (fabs(testBestiole.getOrientation() - expectedOrientation) < 1e-6) {
        std::cout << "kamikaze : test doBehaviour With Neighbors PASSED\n";
    } else {
        std::cout << "kamikaze : test doBehaviour With Neighbors FAILED\n";
    }
}


