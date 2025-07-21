#include "game.cpp"

int main() {
	bool notAWinner;

	Game aGame;

	aGame.add("Chet");
	aGame.add("Pat");
	aGame.add("Sue");

	do {
		aGame.rolling();

		if (rand() % 9 == 7) {
			notAWinner = aGame.wrongAnswer();
		}
		else {
			notAWinner = aGame.wasCorrectlyAnswered();
		}
	} while (notAWinner);

	return 0;
}
