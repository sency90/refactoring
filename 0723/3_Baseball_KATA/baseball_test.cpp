#include "gmock/gmock.h"
#include "baseball.cpp"
using namespace testing;

class BaseballFixture: public Test {
public:
	Baseball game;
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
}
