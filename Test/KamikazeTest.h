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
    friend bool operator==(const Bestiole &b1, const Bestiole &b2);
};

#endif //KAMIKAZETEST_H
