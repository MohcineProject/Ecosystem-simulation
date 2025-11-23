#include <gtest/gtest.h>
#include "Behaviours/Behaviour.h"
#include "Behaviours/Gregarious.h"
#include "Behaviours/Fearful.h"
#include "Behaviours/Kamikaze.h"
#include "Behaviours/Cautious.h"
#include "Behaviours/MultipleBehaviour.h"
#include "Bestioles/Bestiole.h"
#include "Aquarium/Aquarium.h"
#include <set>
#include <cmath>

// Test fixture for Behaviour tests
class BehaviourTest : public ::testing::Test {
protected:
    void SetUp() override {
        aquarium = new Aquarium(100, 100, 30);
        bestiole1 = new Bestiole(10.0);
        bestiole2 = new Bestiole(15.0);
        bestiole3 = new Bestiole(12.0);
        
        // Set up positions and orientations for testing
        bestiole1->setCoordx(10);
        bestiole1->setCoordy(10);
        bestiole1->setOrientation(0.0);
        
        bestiole2->setCoordx(20);
        bestiole2->setCoordy(20);
        bestiole2->setOrientation(M_PI / 4);
        
        bestiole3->setCoordx(30);
        bestiole3->setCoordy(15);
        bestiole3->setOrientation(M_PI / 2);
    }
    
    void TearDown() override {
        delete bestiole1;
        delete bestiole2;
        delete bestiole3;
        delete aquarium;
    }
    
    Aquarium* aquarium;
    Bestiole* bestiole1;
    Bestiole* bestiole2;
    Bestiole* bestiole3;
};

// Test Gregarious behaviour
TEST_F(BehaviourTest, GregariousConstructorSetsType) {
    Gregarious gregarious(bestiole1);
    EXPECT_EQ("Gregaire", gregarious.getType());
}

TEST_F(BehaviourTest, GregariousAlignsWithAverageDirection) {
    Gregarious gregarious(bestiole1);
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    
    double initialOrientation = bestiole1->getOrientation();
    gregarious.doBehaviour(neighbors);
    
    // Should have changed orientation to average
    EXPECT_NE(initialOrientation, bestiole1->getOrientation());
}

TEST_F(BehaviourTest, GregariousWithNoNeighborsDoesNothing) {
    Gregarious gregarious(bestiole1);
    std::set<Bestiole*> emptyNeighbors;
    
    double initialOrientation = bestiole1->getOrientation();
    gregarious.doBehaviour(emptyNeighbors);
    
    // Orientation should remain unchanged
    EXPECT_DOUBLE_EQ(initialOrientation, bestiole1->getOrientation());
}

TEST_F(BehaviourTest, GregariousCalculatesCorrectAverage) {
    Gregarious gregarious(bestiole1);
    bestiole1->setOrientation(0.0);
    bestiole2->setOrientation(M_PI);
    bestiole3->setOrientation(M_PI);
    
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    gregarious.doBehaviour(neighbors);
    
    // Average should be approximately PI
    EXPECT_NEAR(M_PI, bestiole1->getOrientation(), 0.01);
}

// Test Fearful behaviour
TEST_F(BehaviourTest, FearfulConstructorSetsType) {
    Fearful fearful(bestiole1);
    EXPECT_EQ("Fearful", fearful.getType());
}

TEST_F(BehaviourTest, FearfulIncreasesSpeedWhenDense) {
    Fearful fearful(bestiole1);
    std::set<Bestiole*> denseNeighbors;
    
    // Create enough neighbors to trigger fearful behavior
    for (int i = 0; i < 10; i++) {
        Bestiole* b = new Bestiole(10.0);
        denseNeighbors.insert(b);
    }
    
    double initialSpeed = bestiole1->getActualSpeed();
    fearful.doBehaviour(denseNeighbors);
    
    // Speed should have increased
    EXPECT_GE(bestiole1->getActualSpeed(), initialSpeed);
    
    // Cleanup
    for (auto* b : denseNeighbors) {
        delete b;
    }
}

TEST_F(BehaviourTest, FearfulChangesDirection) {
    Fearful fearful(bestiole1);
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    
    // Ensure bestioles have different coordinates
    bestiole1->setCoordx(10);
    bestiole1->setCoordy(10);
    bestiole2->setCoordx(20);
    bestiole2->setCoordy(20);
    bestiole3->setCoordx(30);
    bestiole3->setCoordy(15);
    
    double initialOrientation = bestiole1->getOrientation();
    fearful.doBehaviour(neighbors);
    
    // Direction should have changed (neighbors.size() >= DENSITE_BESTIOLE which is 1)
    EXPECT_NE(initialOrientation, bestiole1->getOrientation());
}

// Test Kamikaze behaviour
TEST_F(BehaviourTest, KamikazeConstructorSetsType) {
    Kamikaze kamikaze(bestiole1);
    EXPECT_EQ("Kamikaze", kamikaze.getType());
}

TEST_F(BehaviourTest, KamikazeMovesTowardsClosestNeighbor) {
    Kamikaze kamikaze(bestiole1);
    
    // Ensure bestioles have different coordinates
    bestiole1->setCoordx(10);
    bestiole1->setCoordy(10);
    bestiole2->setCoordx(20);
    bestiole2->setCoordy(20);
    bestiole3->setCoordx(30);
    bestiole3->setCoordy(15);
    
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    double initialOrientation = bestiole1->getOrientation();
    kamikaze.doBehaviour(neighbors);
    
    // Direction should have changed to move towards closest neighbor
    EXPECT_NE(initialOrientation, bestiole1->getOrientation());
}

TEST_F(BehaviourTest, KamikazeWithNoNeighborsDoesNothing) {
    Kamikaze kamikaze(bestiole1);
    std::set<Bestiole*> emptyNeighbors;
    
    double initialOrientation = bestiole1->getOrientation();
    kamikaze.doBehaviour(emptyNeighbors);
    
    // Orientation should remain unchanged
    EXPECT_DOUBLE_EQ(initialOrientation, bestiole1->getOrientation());
}

// Test Cautious behaviour
TEST_F(BehaviourTest, CautiousConstructorSetsType) {
    Cautious cautious(bestiole1);
    EXPECT_EQ("Cautious", cautious.getType());
}

TEST_F(BehaviourTest, CautiousAvoidsCollisions) {
    Cautious cautious(bestiole1);
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    
    double initialOrientation = bestiole1->getOrientation();
    cautious.doBehaviour(neighbors);
    
    // Direction should have changed to avoid collisions
    EXPECT_NE(initialOrientation, bestiole1->getOrientation());
}

// Test MultipleBehaviour
TEST_F(BehaviourTest, MultipleBehaviourConstructorSetsType) {
    MultipleBehaviour multiple(bestiole1);
    EXPECT_EQ("Multiple", multiple.getType());
}

TEST_F(BehaviourTest, MultipleBehaviourConstructorWithBehaviours) {
    std::vector<std::string> behaviours = {"Cautious", "Fearful"};
    MultipleBehaviour multiple(bestiole1, behaviours);
    EXPECT_EQ("Multiple", multiple.getType());
    EXPECT_NE(nullptr, multiple.getBehaviour());
}

TEST_F(BehaviourTest, MultipleBehaviourSwitchesBehaviours) {
    MultipleBehaviour multiple(bestiole1);
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    
    // Execute multiple times to trigger behavior switching
    double orientation1 = bestiole1->getOrientation();
    multiple.doBehaviour(neighbors);
    double orientation2 = bestiole1->getOrientation();
    
    // Should have some behavior applied
    EXPECT_NE(orientation1, orientation2);
}

// Test Behaviour base class closestBestiole method
TEST_F(BehaviourTest, ClosestBestioleReturnsNullptrWhenEmpty) {
    Gregarious gregarious(bestiole1);
    std::set<Bestiole*> emptyNeighbors;
    
    Bestiole* closest = gregarious.closestBestiole(emptyNeighbors);
    EXPECT_EQ(nullptr, closest);
}

TEST_F(BehaviourTest, ClosestBestioleReturnsCorrectBestiole) {
    Gregarious gregarious(bestiole1);
    std::set<Bestiole*> neighbors = {bestiole2, bestiole3};
    
    Bestiole* closest = gregarious.closestBestiole(neighbors);
    EXPECT_NE(nullptr, closest);
    EXPECT_TRUE(neighbors.find(closest) != neighbors.end());
}

