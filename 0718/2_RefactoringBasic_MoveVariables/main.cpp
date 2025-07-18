#include <iostream>
#include "gmock/gmock.h"

class Player {
private:
    std::string name = "hwan";
    int level_ = 10;
    int hp_ = 180;
    int mp_ = 200;

public:
    Player(const std::string & name, int level, int hp, int mp):name(name), level_(level), hp_(hp), mp_(mp) {}

    void AddLevel(int level) {
        level_ += level;
    }
    void AddHp(int hp) {
        hp_ += hp;
    }
    void AddMp(int mp) {
        mp_ += mp;
    }

    int GetHp() const {
        return hp_;
    }
    int GetMp() const {
        return mp_;
    }
    int GetLevel() const {
        return level_;
    }
};


TEST(Game, GamePlayerEffect) {
    Player player("hwan", 10, 180, 200);
    // level up effect 
	player.AddLevel(1);
	player.AddHp(10);
	player.AddMp(-20);

    EXPECT_EQ(11, player.GetLevel()); 
    EXPECT_EQ(190, player.GetHp()); 
    EXPECT_EQ(180, player.GetMp()); 
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
