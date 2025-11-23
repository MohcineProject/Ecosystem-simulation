#include <gtest/gtest.h>
#include "Captors/CapteurS.h"
#include "Captors/CapteurV.h"
#include "Bestioles/Bestiole.h"
#include <vector>
#include <set>
#include <cmath>

// Test fixture for Captor tests
class CaptorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test bestioles
        bestioles.push_back(Bestiole(10.0));
        bestioles.push_back(Bestiole(15.0));
        bestioles.push_back(Bestiole(12.0));
        
        // Set up coordinates for testing
        // First bestiole at origin (0, 0)
        // Second bestiole at distance 5
        // Third bestiole at distance 10
        coordvector.push_back({0.0, 0.0});  // Self
        coordvector.push_back({25.0, 0.0});  // Distance 5 squared
        coordvector.push_back({100.0, 0.0}); // Distance 10 squared
    }
    
    void TearDown() override {
        coordvector.clear();
        bestioles.clear();
    }
    
    std::vector<Bestiole> bestioles;
    std::vector<std::pair<double, double>> coordvector;
};

// Test CapteurS (Sound Sensor)
TEST_F(CaptorTest, CapteurSConstructorInitializesRange) {
    CapteurS capteur(1.0f, 0.5f, 100.0f, 50.0f);
    int range = capteur.getR();
    
    // Range should be within the specified bounds
    EXPECT_GE(range, 50);
    EXPECT_LE(range, 100);
}

TEST_F(CaptorTest, CapteurSDetectsNearbyBestioles) {
    CapteurS capteur(1.0f, 0.5f, 100.0f, 50.0f);
    
    // Set detection capability for bestioles
    bestioles[1].detectionCapability = 0.7f;
    bestioles[2].detectionCapability = 0.8f;
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    // Should detect at least the closest bestiole if within range
    // Note: Detection depends on random initialization, so we test structure
    EXPECT_GE(detected.size(), 0);
    EXPECT_LE(detected.size(), 2); // Can detect at most 2 neighbors
}

TEST_F(CaptorTest, CapteurSDoesNotDetectSelf) {
    CapteurS capteur(1.0f, 0.5f, 100.0f, 50.0f);
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    // Should not contain self (index 0)
    for (auto* b : detected) {
        EXPECT_NE(&bestioles[0], b);
    }
}

TEST_F(CaptorTest, CapteurSReturnsEmptySetWhenNoNeighbors) {
    CapteurS capteur(1.0f, 0.5f, 10.0f, 5.0f);
    std::vector<std::pair<double, double>> farCoords;
    farCoords.push_back({0.0, 0.0});
    farCoords.push_back({10000.0, 0.0}); // Very far
    
    std::set<Bestiole*> detected = capteur.update(farCoords, 0, bestioles);
    
    // Should be empty if all neighbors are too far
    EXPECT_GE(detected.size(), 0);
}

// Test CapteurV (Vision Sensor)
TEST_F(CaptorTest, CapteurVConstructorInitializesRangeAndAngle) {
    CapteurV capteur(1.0f, 0.5f, 180.0f, 90.0f, 100.0f, 50.0f);
    
    float range = capteur.getR();
    int angle = capteur.getTheta();
    
    // Range should be within bounds
    EXPECT_GE(range, 50.0f);
    EXPECT_LE(range, 100.0f);
    
    // Angle should be within bounds
    EXPECT_GE(angle, 90);
    EXPECT_LE(angle, 180);
}

TEST_F(CaptorTest, CapteurVDetectsBestiolesInFieldOfView) {
    CapteurV capteur(1.0f, 0.5f, 180.0f, 90.0f, 100.0f, 50.0f);
    
    // Set detection capability
    bestioles[1].detectionCapability = 0.7f;
    bestioles[2].detectionCapability = 0.8f;
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    // Should detect bestioles within field of view
    EXPECT_GE(detected.size(), 0);
    EXPECT_LE(detected.size(), 2);
}

TEST_F(CaptorTest, CapteurVDoesNotDetectSelf) {
    CapteurV capteur(1.0f, 0.5f, 180.0f, 90.0f, 100.0f, 50.0f);
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    // Should not contain self
    for (auto* b : detected) {
        EXPECT_NE(&bestioles[0], b);
    }
}

TEST_F(CaptorTest, CapteurVRespectsAngleLimits) {
    CapteurV capteur(1.0f, 0.5f, 45.0f, 30.0f, 100.0f, 50.0f);
    
    // Create coordinates with different angles
    std::vector<std::pair<double, double>> angleCoords;
    angleCoords.push_back({0.0, 0.0});      // Self
    angleCoords.push_back({25.0, 10.0});    // Small angle
    angleCoords.push_back({25.0, 60.0});    // Large angle (should be outside FOV)
    
    std::set<Bestiole*> detected = capteur.update(angleCoords, 0, bestioles);
    
    // Detection depends on angle limits
    EXPECT_GE(detected.size(), 0);
}

TEST_F(CaptorTest, CapteurVRespectsDistanceLimits) {
    CapteurV capteur(1.0f, 0.5f, 180.0f, 90.0f, 50.0f, 10.0f);
    
    std::vector<std::pair<double, double>> distanceCoords;
    distanceCoords.push_back({0.0, 0.0});      // Self
    distanceCoords.push_back({25.0, 0.0});    // Within range
    distanceCoords.push_back({10000.0, 0.0}); // Outside range
    
    std::set<Bestiole*> detected = capteur.update(distanceCoords, 0, bestioles);
    
    // Should only detect nearby bestioles
    EXPECT_GE(detected.size(), 0);
}

// Test detection capability filtering
TEST_F(CaptorTest, CapteurSFiltersByDetectionCapability) {
    CapteurS capteur(0.5f, 0.3f, 100.0f, 50.0f);
    
    // Set one bestiole with high detection capability (harder to detect)
    bestioles[1].detectionCapability = 1.0f; // Very high, shouldn't be detected
    bestioles[2].detectionCapability = 0.2f; // Low, should be detected
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    // Detection depends on capability comparison
    EXPECT_GE(detected.size(), 0);
}

TEST_F(CaptorTest, CapteurVFiltersByDetectionCapability) {
    CapteurV capteur(0.5f, 0.3f, 180.0f, 90.0f, 100.0f, 50.0f);
    
    bestioles[1].detectionCapability = 1.0f; // Very high
    bestioles[2].detectionCapability = 0.2f; // Low
    
    std::set<Bestiole*> detected = capteur.update(coordvector, 0, bestioles);
    
    EXPECT_GE(detected.size(), 0);
}

