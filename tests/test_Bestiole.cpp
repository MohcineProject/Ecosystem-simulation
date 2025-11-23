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
