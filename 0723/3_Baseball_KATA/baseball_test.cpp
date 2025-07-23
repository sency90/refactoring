#include "gmock/gmock.h"
#include "baseball.cpp"
using namespace testing;

class BaseballFixture: public Test {
public:
	Baseball game{"123"};
	void assertIllegalArgument(const string& guessNumber) {
		try {
			game.guess(string(guessNumber));
			FAIL();
		} catch(exception ex) {
			//PASS
		}
	}
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchedNumber) {
	GuessResult result = game.guess("123");

	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}
