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

	bool isEqual = (result == GuessResult{true, 3, 0});
	EXPECT_TRUE(isEqual);
}

TEST_F(BaseballFixture, S2B0) {
	GuessResult result = game.guess("124");

	bool isEqual = (result == GuessResult{false, 2, 0});
	EXPECT_TRUE(isEqual);
}

TEST_F(BaseballFixture, S1B2) {
	GuessResult result = game.guess("132");

	bool isEqual = (result == GuessResult{false, 1, 2});
	EXPECT_TRUE(isEqual);
}
