//
// Created by mouha1505 on 05/12/24.
//

#ifndef KAMIKAZETEST_H
#define KAMIKAZETEST_H
#include "CreateBestioleForTest.h"

class KamikazeTest : public CreateBestioleForTest {
    public:
    KamikazeTest() = default;

    static void testDoBehaviour_NoNeighbors();

    static void testDoBehaviour_WithNeighbors();
};

#endif //KAMIKAZETEST_H
