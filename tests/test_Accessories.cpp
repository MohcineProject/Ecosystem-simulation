#include <gtest/gtest.h>
#include "Accessories/Fins.h"
#include "Accessories/Carapace.h"
#include "Accessories/Camouflage.h"
#include "Accessories/Accessoire.h"
#include <cmath>

// Test Fins accessory
TEST(FinsTest, ConstructorSetsSpeedMultiplier) {
    Fins fins(1.5);
    EXPECT_DOUBLE_EQ(1.5, fins.getSpeedFactor());
}

TEST(FinsTest, GetSpeedFactorReturnsMultiplier) {
    Fins fins(2.0);
    EXPECT_DOUBLE_EQ(2.0, fins.getSpeedFactor());
}

TEST(FinsTest, GetTypeReturnsFins) {
    Fins fins(1.0);
    EXPECT_EQ("Fins", fins.getType());
}

TEST(FinsTest, SetSpeedMultiplierUpdatesValue) {
    Fins fins(1.0);
    fins.setSpeedMultiplier(2.5);
    EXPECT_DOUBLE_EQ(2.5, fins.getSpeedFactor());
}

TEST(FinsTest, SpeedMultiplierCanBeLessThanOne) {
    Fins fins(0.5);
    EXPECT_DOUBLE_EQ(0.5, fins.getSpeedFactor());
}

TEST(FinsTest, SpeedMultiplierCanBeGreaterThanOne) {
    Fins fins(3.0);
    EXPECT_DOUBLE_EQ(3.0, fins.getSpeedFactor());
}

// Test Carapace accessory
TEST(CarapaceTest, ConstructorSetsAllValues) {
    Carapace carapace(0.8f, 1.5f, 0.7f);
    EXPECT_FLOAT_EQ(0.8f, carapace.getCapDetect());
    EXPECT_FLOAT_EQ(1.5f, carapace.getResistanceFactor());
    EXPECT_NEAR(0.7, carapace.getSpeedFactor(), 0.001);
}

TEST(CarapaceTest, GetSpeedFactorReturnsSpeedFactor) {
    Carapace carapace(0.5f, 2.0f, 0.6f);
    EXPECT_NEAR(0.6, carapace.getSpeedFactor(), 0.001);
}

TEST(CarapaceTest, GetTypeReturnsCarapace) {
    Carapace carapace(0.5f, 1.0f, 0.8f);
    EXPECT_EQ("Carapace", carapace.getType());
}

TEST(CarapaceTest, GetCapDetectReturnsDetectionModifier) {
    Carapace carapace(0.7f, 1.2f, 0.9f);
    EXPECT_FLOAT_EQ(0.7f, carapace.getCapDetect());
}

TEST(CarapaceTest, GetResistanceFactorReturnsResistance) {
    Carapace carapace(0.6f, 1.8f, 0.75f);
    EXPECT_FLOAT_EQ(1.8f, carapace.getResistanceFactor());
}

TEST(CarapaceTest, CarapaceReducesSpeed) {
    Carapace carapace(0.5f, 1.0f, 0.5f);
    // Speed factor should be less than 1.0 (reduces speed)
    EXPECT_LT(carapace.getSpeedFactor(), 1.0);
}

TEST(CarapaceTest, CarapaceIncreasesResistance) {
    Carapace carapace(0.5f, 2.0f, 0.8f);
    // Resistance factor should be greater than 1.0 (increases resistance)
    EXPECT_GT(carapace.getResistanceFactor(), 1.0);
}

// Test Camouflage accessory
TEST(CamouflageTest, ConstructorSetsDetectionModifier) {
    Camouflage camouflage(0.3f);
    EXPECT_FLOAT_EQ(0.3f, camouflage.getDetectionModifier());
}

TEST(CamouflageTest, GetDetectionModifierReturnsValue) {
    Camouflage camouflage(0.5f);
    EXPECT_FLOAT_EQ(0.5f, camouflage.getDetectionModifier());
}

TEST(CamouflageTest, GetTypeReturnsCamouflage) {
    Camouflage camouflage(0.4f);
    EXPECT_EQ("Camouflage", camouflage.getType());
}

TEST(CamouflageTest, GetSpeedFactorReturnsOne) {
    Camouflage camouflage(0.5f);
    // Camouflage doesn't affect speed
    EXPECT_DOUBLE_EQ(1.0, camouflage.getSpeedFactor());
}

TEST(CamouflageTest, CamouflageReducesDetection) {
    Camouflage camouflage(0.3f);
    // Detection modifier should be less than 1.0 (reduces detectability)
    EXPECT_LT(camouflage.getDetectionModifier(), 1.0f);
}

TEST(CamouflageTest, DetectionModifierCanBeZero) {
    Camouflage camouflage(0.0f);
    EXPECT_FLOAT_EQ(0.0f, camouflage.getDetectionModifier());
}

// Test Accessoire base class interface
TEST(AccessoireTest, FinsIsAccessoire) {
    Fins fins(1.5);
    Accessoire* accessory = &fins;
    EXPECT_NE(nullptr, accessory);
    EXPECT_EQ("Fins", accessory->getType());
}

TEST(AccessoireTest, CarapaceIsAccessoire) {
    Carapace carapace(0.5f, 1.0f, 0.8f);
    Accessoire* accessory = &carapace;
    EXPECT_NE(nullptr, accessory);
    EXPECT_EQ("Carapace", accessory->getType());
}

TEST(AccessoireTest, CamouflageIsAccessoire) {
    Camouflage camouflage(0.5f);
    Accessoire* accessory = &camouflage;
    EXPECT_NE(nullptr, accessory);
    EXPECT_EQ("Camouflage", accessory->getType());
}

TEST(AccessoireTest, PolymorphicGetSpeedFactor) {
    Fins fins(2.0);
    Carapace carapace(0.5f, 1.0f, 0.5f);
    Camouflage camouflage(0.5f);
    
    Accessoire* accessories[] = {&fins, &carapace, &camouflage};
    
    EXPECT_DOUBLE_EQ(2.0, accessories[0]->getSpeedFactor());
    EXPECT_DOUBLE_EQ(0.5, accessories[1]->getSpeedFactor());
    EXPECT_DOUBLE_EQ(1.0, accessories[2]->getSpeedFactor());
}

