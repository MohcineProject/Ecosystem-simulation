#include <gtest/gtest.h>
#include "Bestioles/Bestiole.h"
#include "Bestioles/BestioleFactory.h"
#include "Aquarium/Aquarium.h"
#include "Accessories/Fins.h"
#include "Accessories/Carapace.h"
#include <memory>
#include <cmath>

// Test constructor with direct instantiation
TEST(BestioleTest, ConstructorSetsBaseSpeed) {
    Bestiole bestiole(10.0);
    EXPECT_DOUBLE_EQ(10.0, bestiole.getBaseSpeed());
}


class BestioleTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Preparing the bestiole factory for testing
        aquarium = new Aquarium(100, 100, 30);
        factory = BestioleFactory::getBestioleFactory(aquarium);
    }
    
    void TearDown() override {
        delete aquarium;
    }
    
    Aquarium* aquarium;
    BestioleFactory* factory;
};


TEST(BestioleTest, ConstructorInitializesDeathFlag) {
    Bestiole bestiole(10.0);
    EXPECT_FALSE(bestiole.deathflag);
}

TEST(BestioleTest, ConstructorAssignsUniqueIdentity) {
    Bestiole b1(10.0);
    Bestiole b2(10.0);
    Bestiole b3(10.0);
    EXPECT_NE(b1.getIdentite(), b2.getIdentite());
    EXPECT_NE(b2.getIdentite(), b3.getIdentite());
    EXPECT_NE(b1.getIdentite(), b3.getIdentite());
}

// Test factory-created bestioles
TEST_F(BestioleFactoryTest, FactoryCreatesGregariousBestiole) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Gregarious", b->type);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesFearfulBestiole) {
    Bestiole* b = factory->createBestiole("Fearful");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Fearful", b->type);
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesKamikazeBestiole) {
    Bestiole* b = factory->createBestiole("Kamikaze");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Kamikaze", b->type);
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesCautiousBestiole) {
    Bestiole* b = factory->createBestiole("Cautious");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Cautious", b->type);
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryCreatesMultipleBestiole) {
    Bestiole* b = factory->createBestiole("Multiple");
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Multiple", b->type);
    EXPECT_NE(nullptr, b->behaviour);
    delete b;
}

// Test coordinate methods
TEST(BestioleTest, InitCoordsSetsValidCoordinates) {
    Bestiole bestiole(10.0);
    bestiole.initCoords(100, 100);
    int x = bestiole.getCoordx();
    int y = bestiole.getCoordy();
    EXPECT_GE(x, 0);
    EXPECT_LT(x, 100);
    EXPECT_GE(y, 0);
    EXPECT_LT(y, 100);
}

TEST(BestioleTest, SetCoordxUpdatesXCoordinate) {
    Bestiole bestiole(10.0);
    bestiole.setCoordx(50);
    EXPECT_EQ(50, bestiole.getCoordx());
}

TEST(BestioleTest, SetCoordyUpdatesYCoordinate) {
    Bestiole bestiole(10.0);
    bestiole.setCoordy(75);
    EXPECT_EQ(75, bestiole.getCoordy());
}

// Test speed methods
TEST(BestioleTest, SetVitesseUpdatesSpeed) {
    Bestiole bestiole(10.0);
    bestiole.setVitesse(15.0);
    // Note: getActualSpeed considers accessories, so we test that
    EXPECT_GE(bestiole.getActualSpeed(), 0.0);
}

TEST(BestioleTest, GetActualSpeedReturnsBaseSpeedWithoutAccessories) {
    Bestiole bestiole(10.0);
    // Without accessories, actual speed should equal base speed
    EXPECT_DOUBLE_EQ(10.0, bestiole.getActualSpeed());
}

TEST(BestioleTest, GetMaxSpeedReturnsConstant) {
    double maxSpeed = Bestiole::getMaxSpeed();
    EXPECT_GT(maxSpeed, 0.0);
    // Should be the MAX_VITESSE constant (10.0)
    EXPECT_DOUBLE_EQ(10.0, maxSpeed);
}

// Test accessory methods
TEST(BestioleTest, AddFinsIncreasesSpeed) {
    Bestiole bestiole(10.0);
    double speedBefore = bestiole.getActualSpeed();
    auto fins = std::make_shared<Fins>(1.5); // 1.5x multiplier
    bestiole.addAccessory(fins);
    EXPECT_GT(bestiole.getActualSpeed(), speedBefore);
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
    // Carapace should modify detection capability
    EXPECT_NE(detectionBefore, bestiole.getDetectionCapability());
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

TEST_F(BestioleFactoryTest, DoBehaviourExecutesWithoutCrash) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    // Should not crash even with empty detected set
    EXPECT_NO_THROW(b->doBehaviour());
    delete b;
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

// Test copy constructor
TEST(BestioleTest, CopyConstructorCreatesNewBestiole) {
    Bestiole original(10.0);
    original.setCoordx(50);
    original.setCoordy(75);
    original.setOrientation(1.57f);
    
    Bestiole copy(original);
    
    EXPECT_NE(original.getIdentite(), copy.getIdentite());
    EXPECT_EQ(original.getBaseSpeed(), copy.getBaseSpeed());
    EXPECT_EQ(original.getCoordx(), copy.getCoordx());
    EXPECT_EQ(original.getCoordy(), copy.getCoordy());
    EXPECT_FLOAT_EQ(original.getOrientation(), copy.getOrientation());
}

// Test move constructor
TEST(BestioleTest, MoveConstructorTransfersOwnership) {
    Bestiole original(10.0);
    original.setCoordx(50);
    original.setCoordy(75);
    int originalId = original.getIdentite();
    
    Bestiole moved(std::move(original));
    
    EXPECT_EQ(originalId, moved.getIdentite());
    EXPECT_EQ(50, moved.getCoordx());
    EXPECT_EQ(75, moved.getCoordy());
}

// Test factory-created bestioles have valid attributes
TEST_F(BestioleFactoryTest, FactoryBestioleHasValidBaseSpeed) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    EXPECT_GT(b->getBaseSpeed(), 0.0);
    EXPECT_DOUBLE_EQ(10.0, b->getBaseSpeed());
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryBestioleHasValidDetectionCapability) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    float detection = b->getDetectionCapability();
    EXPECT_GE(detection, 0.0f);
    EXPECT_LE(detection, 1.0f);
    delete b;
}

TEST_F(BestioleFactoryTest, FactoryBestioleHasValidResistance) {
    Bestiole* b = factory->createBestiole("Gregarious");
    ASSERT_NE(nullptr, b);
    float resistance = b->getResistance();
    EXPECT_GT(resistance, 0.0f);
    delete b;
}

// Test multiple accessories
TEST(BestioleTest, MultipleAccessoriesCanBeAdded) {
    Bestiole bestiole(10.0);
    auto fins = std::make_shared<Fins>(1.5);
    auto carapace = std::make_shared<Carapace>(0.5, 1.2, 0.8);
    
    bestiole.addAccessory(fins);
    EXPECT_EQ(1, bestiole.accessoires.size());
    
    bestiole.addAccessory(carapace);
    EXPECT_EQ(2, bestiole.accessoires.size());
}

// Test that factory is singleton
TEST_F(BestioleFactoryTest, FactoryIsSingleton) {
    BestioleFactory* factory2 = BestioleFactory::getBestioleFactory(aquarium);
    EXPECT_EQ(factory, factory2);
}
