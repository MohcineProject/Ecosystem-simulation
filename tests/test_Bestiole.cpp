#include <gtest/gtest.h>
#include "Bestioles/Bestiole.h"
#include "Bestioles/BestioleFactory.h"
#include "Aquarium/Aquarium.h"
#include "Aquarium/Milieu.h"
#include "Accessories/Fins.h"
#include "Accessories/Carapace.h"
#include <memory>
#include <cmath>


TEST(BestioleTest, ConstructorSetsDefaultSpeed){
    Bestiole bestiole(10.0);
    EXPECT_DOUBLE_EQ(10.0, bestiole.getBaseSpeed());
}

TEST(BestioleTest, ConstructorGivesUniqueIdentity){
    // Get the starting counter value (we could start from a non zero if other tests start first)
    int startId = Bestiole::getNextId();
    
    Bestiole b1(10.0);
    Bestiole b2(10.0);
    Bestiole b3(10.0);
    
    // Check that the next ID counter has been incremented by 3
    EXPECT_EQ(Bestiole::getNextId(), startId + 3);
    // Verify that each bestiole has a unique ID
    EXPECT_NE(b1.getIdentite(), b2.getIdentite());
    EXPECT_NE(b2.getIdentite(), b3.getIdentite());
    EXPECT_NE(b1.getIdentite(), b3.getIdentite());
}

TEST(BestioleTest, InitCoordsSetsValidCoordinates) {
    Bestiole bestiole(10.0);
    bestiole.initCoords(100, 100);
    EXPECT_GE(bestiole.getCoordx(), 0);
    EXPECT_LT(bestiole.getCoordx(), 100);
    EXPECT_GE(bestiole.getCoordy(), 0);
    EXPECT_LT(bestiole.getCoordy(), 100);
}

TEST(BestioleTest, BestioleIsMovingCorrectly){
    Bestiole b(10);
    // Set coordinates explicitly
    b.setCoordx(100);
    b.setCoordy(100);
    b.setOrientation(0.0);
    b.setBehaviorSpeedMultiplier(1.0);  
    
    // Create a Milieu to use action() which calls move() internally
    Milieu milieu(200, 200);
    b.action(milieu);
    
    // With orientation 0.0 and speed 10, we should move 10 units in x direction
    EXPECT_EQ(b.getCoordx(), 110);
    EXPECT_EQ(b.getCoordy(), 100);
}


// Test orientation methods
TEST(BestioleTest, SetOrientationUpdatesOrientation) {
    Bestiole bestiole(10.0);
    float newOrientation = 1.57f; // ~90 degrees
    bestiole.setOrientation(newOrientation);
    EXPECT_FLOAT_EQ(newOrientation, bestiole.getOrientation());
}

TEST(BestioleTest, OrientationIsWithinValidRange) {
    Bestiole bestiole(10.0);
    float orientation = bestiole.getOrientation();
    // Orientation should be between 0 and 2*PI (or reasonable range)
    EXPECT_GE(orientation, 0.0f);
    EXPECT_LE(orientation, 2.0f * M_PI + 1.0f); // Allow some tolerance
}

// Test age and death methods
TEST(BestioleTest, GrowIncrementsAge) {
    Bestiole bestiole(10.0);
    int initialAge = bestiole.myAge;
    bestiole.grow();
    EXPECT_EQ(initialAge + 1, bestiole.myAge);
}

TEST(BestioleTest, GrowDoesNotExceedAgeLimit) {
    Bestiole bestiole(10.0);
    // Set age close to limit
    bestiole.myAge = bestiole.myAgeLimit - 1;
    bestiole.grow();
    EXPECT_LE(bestiole.myAge, bestiole.myAgeLimit);
}

TEST(BestioleTest, AmIOldReturnsFalseWhenYoung) {
    Bestiole bestiole(10.0);
    bestiole.myAge = 0;
    EXPECT_FALSE(bestiole.amIOld());
}

TEST(BestioleTest, AmIOldReturnsTrueWhenAtLimit) {
    Bestiole bestiole(10.0);
    bestiole.myAge = bestiole.myAgeLimit;
    EXPECT_TRUE(bestiole.amIOld());
}

TEST(BestioleTest, DieSetsDeathFlag) {
    Bestiole bestiole(10.0);
    EXPECT_FALSE(bestiole.deathflag);
    bestiole.die();
    EXPECT_TRUE(bestiole.deathflag);
}

// Test accessory methods
TEST(BestioleTest, AddFinsIncreasesSpeed) {
    Bestiole bestiole(5.0); 
    double speedBefore = bestiole.getActualSpeed();
    auto fins = std::make_shared<Fins>(1.5); // 1.5x multiplier
    bestiole.addAccessory(fins);
    double speedAfter = bestiole.getActualSpeed();
    EXPECT_GT(speedAfter, speedBefore);
    EXPECT_DOUBLE_EQ(7.5, speedAfter);  // 5.0 * 1.5 = 7.5
}

TEST(BestioleTest, AddCarapaceModifiesResistance) {
    Bestiole bestiole(10.0);
    float resistanceBefore = bestiole.getResistance();
    auto carapace = std::make_shared<Carapace>(0.5, 1.5, 0.8);
    bestiole.addAccessory(carapace);
    EXPECT_GT(bestiole.getResistance(), resistanceBefore);
}

TEST(BestioleTest, AddCarapaceReducesSpeed) {
    Bestiole bestiole(10.0);
    double speedBefore = bestiole.getActualSpeed();
    auto carapace = std::make_shared<Carapace>(0.5, 1.5, 0.7); // 0.7 speed factor
    bestiole.addAccessory(carapace);
    EXPECT_LT(bestiole.getActualSpeed(), speedBefore);
}

TEST(BestioleTest, AddCarapaceModifiesDetectionCapability) {
    Bestiole bestiole(10.0);
    float detectionBefore = bestiole.getDetectionCapability();
    auto carapace = std::make_shared<Carapace>(0.5, 1.5, 0.8);
    bestiole.addAccessory(carapace);
    EXPECT_NE(detectionBefore, bestiole.getDetectionCapability());
}

// Testing the bestiole factory
// Test fixture for Bestiole tests using factory
class BestioleFactoryTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Create an Aquarium instance for the factory
            // Using small dimensions for testing
            aquarium = new Aquarium(100, 100, 30);
            factory = BestioleFactory::getBestioleFactory(aquarium);
        }
        
        void TearDown() override {
            delete aquarium;
            // Factory is singleton, don't delete
        }
        
        Aquarium* aquarium;
        BestioleFactory* factory;
    };

TEST_F(BestioleFactoryTest, FactoryCreatesGregariousBestiole){
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Gregarious", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    // Detection capability is always set by equip_bestiole
    EXPECT_GE(b->detectionCapability, aquarium->get_camouflage_min());
    EXPECT_LE(b->detectionCapability, aquarium->get_camouflage_max());
    EXPECT_NE(nullptr, b->behaviour);

    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesFearfulBestiole) {
    Bestiole* b = factory->createBestiole("Fearful");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Fearful", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    // Detection capability is always set by equip_bestiole
    EXPECT_GE(b->detectionCapability, aquarium->get_camouflage_min());
    EXPECT_LE(b->detectionCapability, aquarium->get_camouflage_max());
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesKamikazeBestiole) {
    Bestiole* b = factory->createBestiole("Kamikaze");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Kamikaze", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    // Detection capability is always set by equip_bestiole
    EXPECT_GE(b->detectionCapability, aquarium->get_camouflage_min());
    EXPECT_LE(b->detectionCapability, aquarium->get_camouflage_max());
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesCautiousBestiole) {
    Bestiole* b = factory->createBestiole("Cautious");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Cautious", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    // Detection capability is always set by equip_bestiole
    EXPECT_GE(b->detectionCapability, aquarium->get_camouflage_min());
    EXPECT_LE(b->detectionCapability, aquarium->get_camouflage_max());
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesMultipleBehaviorBestiole) {
    Bestiole* b = factory->createBestiole("Multiple");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Multiple", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    // Detection capability is always set by equip_bestiole
    EXPECT_GE(b->detectionCapability, aquarium->get_camouflage_min());
    EXPECT_LE(b->detectionCapability, aquarium->get_camouflage_max());
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

// Test behavior methods
TEST_F(BestioleFactoryTest, SetBehaviourChangesBehaviorType) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Gregarious", b->type);
    
    b->setBehaviour("Fearful");
    EXPECT_EQ("Fearful", b->type);
    EXPECT_NE(nullptr, b->behaviour);
    
    delete b;
}

// Test that factory is singleton
TEST_F(BestioleFactoryTest, FactoryIsSingleton) {
    BestioleFactory* factory2 = BestioleFactory::getBestioleFactory(aquarium);
    EXPECT_EQ(factory, factory2);
}
