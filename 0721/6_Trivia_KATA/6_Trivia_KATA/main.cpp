#include "game.cpp"
#include "game_refactor.cpp"
#include "gmock/gmock.h"

using namespace testing;

class GameFixture: public TestWithParam<int> {
public:
	string playGame(IGame& aGame, int seed) {
		std::ostringstream oss;
		auto oldCoutStreamBuf = std::cout.rdbuf();
		std::cout.rdbuf(oss.rdbuf()); // ���ο� ���۷� redirection

		bool notAWinner;

		//Game aGame;
		srand(seed);

		aGame.add("Chet");
		aGame.add("Pat");
		aGame.add("Sue");

		do {
			int roll = rand() % 6 + 1;
			aGame.rolling(roll);

			if(rand() % 9 == 7) {
				notAWinner = aGame.wrongAnswerQuizAndReturnIsContinueGame();
			} else {
				notAWinner = aGame.correctAnswerQuizAndReturnIsContinueGame();
			}
		} while(notAWinner);

		std::cout.rdbuf(oldCoutStreamBuf); //����
		return oss.str();
	}
};

INSTANTIATE_TEST_SUITE_P( GoldenMaster, GameFixture, Values(1, 50, 100, 777));

TEST_P(GameFixture, GoldenMaster) {
	Game originGame;
	GameRefactor refactorGame;

	int seed = 1;
	string expected = playGame(originGame, seed);
	string actual = playGame(refactorGame, seed);

	EXPECT_EQ(expected, actual);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}