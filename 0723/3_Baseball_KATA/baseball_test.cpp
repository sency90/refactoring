#include "gmock/gmock.h"
#include "baseball.cpp"

TEST(TS, TC1) {
	EXPECT_EQ(1, 1);
}

TEST(BaseballGame, ThrowExceptionWhenInputLengthIsUnmached) {
	Baseball game;
	EXPECT_THROW(game.guess(string("12")), length_error);
}
