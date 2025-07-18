#include <iostream>
#include "gmock/gmock.h"

class Player {
};


TEST(Game, GamePlayerEffect) {
    int level = 10;
    int hp = 180;
    int mp = 200;
    std::string name = "hwan";

    // level up effect 
    hp += 10;
    mp -= 20;
    level += 1; 

    EXPECT_EQ(190, hp); 
    EXPECT_EQ(180, mp); 
    EXPECT_EQ(11, level); 
}

int main() {
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
