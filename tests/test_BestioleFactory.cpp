#include <gtest/gtest.h>
#include "Bestioles/BestioleFactory.h"
#include "Bestioles/Bestiole.h"
#include "Aquarium/Aquarium.h"
#include <string>

// Test fixture for BestioleFactory tests
class BestioleFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
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

// Test singleton pattern
TEST_F(BestioleFactoryTest, GetBestioleFactoryReturnsSameInstance) {
    BestioleFactory* factory2 = BestioleFactory::getBestioleFactory(aquarium);
    
    // Should return the same instance (singleton)
    EXPECT_EQ(factory, factory2);
}

TEST_F(BestioleFactoryTest, FactoryIsNotNull) {
    EXPECT_NE(nullptr, factory);
}

// Test creating different types of bestioles
TEST_F(BestioleFactoryTest, CreateGregariousBestiole) {
    Bestiole* b = factory->createBestiole("Gregarious");
    
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Gregarious", b->type);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreateFearfulBestiole) {
    Bestiole* b = factory->createBestiole("Fearful");
    
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Fearful", b->type);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreateKamikazeBestiole) {
    Bestiole* b = factory->createBestiole("Kamikaze");
    
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Kamikaze", b->type);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreateCautiousBestiole) {
    Bestiole* b = factory->createBestiole("Cautious");
    
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Cautious", b->type);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreateMultipleBestiole) {
    Bestiole* b = factory->createBestiole("Multiple");
    
    ASSERT_NE(nullptr, b);
    EXPECT_EQ("Multiple", b->type);
    
    delete b;
}

// Test that created bestioles have valid properties
TEST_F(BestioleFactoryTest, CreatedBestioleHasValidSpeed) {
    Bestiole* b = factory->createBestiole("Gregarious");
    
    ASSERT_NE(nullptr, b);
    EXPECT_GT(b->getBaseSpeed(), 0.0);
    EXPECT_GT(b->getActualSpeed(), 0.0);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreatedBestioleHasValidIdentity) {
    Bestiole* b1 = factory->createBestiole("Gregarious");
    Bestiole* b2 = factory->createBestiole("Fearful");
    
    ASSERT_NE(nullptr, b1);
    ASSERT_NE(nullptr, b2);
    
    // Each bestiole should have a unique identity
    EXPECT_NE(b1->getIdentite(), b2->getIdentite());
    
    delete b1;
    delete b2;
}

TEST_F(BestioleFactoryTest, CreatedBestioleHasValidOrientation) {
    Bestiole* b = factory->createBestiole("Kamikaze");
    
    ASSERT_NE(nullptr, b);
    
    // Orientation should be in valid range [0, 2*PI)
    float orientation = b->getOrientation();
    EXPECT_GE(orientation, 0.0f);
    EXPECT_LT(orientation, 2.0f * M_PI);
    
    delete b;
}

TEST_F(BestioleFactoryTest, CreatedBestioleIsNotDead) {
    Bestiole* b = factory->createBestiole("Cautious");
    
    ASSERT_NE(nullptr, b);
    EXPECT_FALSE(b->deathflag);
    
    delete b;
}

// Test creating multiple bestioles of same type
TEST_F(BestioleFactoryTest, CreateMultipleBestiolesOfSameType) {
    Bestiole* b1 = factory->createBestiole("Gregarious");
    Bestiole* b2 = factory->createBestiole("Gregarious");
    Bestiole* b3 = factory->createBestiole("Gregarious");
    
    ASSERT_NE(nullptr, b1);
    ASSERT_NE(nullptr, b2);
    ASSERT_NE(nullptr, b3);
    
    // All should have same type
    EXPECT_EQ("Gregarious", b1->type);
    EXPECT_EQ("Gregarious", b2->type);
    EXPECT_EQ("Gregarious", b3->type);
    
    // But different identities
    EXPECT_NE(b1->getIdentite(), b2->getIdentite());
    EXPECT_NE(b2->getIdentite(), b3->getIdentite());
    EXPECT_NE(b1->getIdentite(), b3->getIdentite());
    
    delete b1;
    delete b2;
    delete b3;
}

// Test that factory can equip bestioles with accessories
TEST_F(BestioleFactoryTest, CreatedBestioleMayHaveAccessories) {
    Bestiole* b = factory->createBestiole("Gregarious");
    
    ASSERT_NE(nullptr, b);
    
    // Bestiole may or may not have accessories (random)
    // We just verify it doesn't crash and bestiole is valid
    EXPECT_NE(nullptr, b);
    
    delete b;
}

// Test invalid type handling (if factory handles it)
TEST_F(BestioleFactoryTest, CreateBestioleWithInvalidType) {
    // This test depends on factory implementation
    // If factory returns nullptr for invalid types, test that
    // If factory throws exception, use EXPECT_THROW
    // For now, we'll test that it doesn't crash
    Bestiole* b = factory->createBestiole("InvalidType");
    
    // Factory might return nullptr or create a default bestiole
    // This depends on implementation
    if (b != nullptr) {
        delete b;
    }
}

