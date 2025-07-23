#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

struct GuessResult {
private:
	int strikes;
	int balls;

public:
	GuessResult():strikes(0), balls(0) {}
	GuessResult(int strikes, int balls): strikes(strikes), balls(balls) {}
	bool operator==(const GuessResult& rhs) const {
		return strikes == rhs.strikes && balls == rhs.balls;
	}

	bool isSolved() const {
		return strikes==3;
	}
	int getStrikes() const {
		return strikes;
	}
	int getBalls() const {
		return balls;
	}

	void countStrike() {
		strikes++;
	}
	void countBall() {
		balls++;
	}
};


class Baseball {
public:
	explicit Baseball(const string& question): question(question) {}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		if(guessNumber == question) {
			return answerGuessResult;
		}
		GuessResult guessResult;
		for(int i=0; i<question.size(); i++) {
			for(int j=0; j<guessNumber.size(); j++) {
				if(question[i] != guessNumber[j]) continue;
				if(i == j) guessResult.countStrike();
				else guessResult.countBall();
				break;
			}
		}
		return guessResult;
	}
	void assertIllegalArgument(const std::string& guessNumber) {
		if(guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for(char ch : guessNumber) {
			if(isdigit(ch)) continue;
			throw invalid_argument("Must be number");
		}

		if(isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}
	bool isDuplicatedNumber(const std::string& guessNumber) {
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}
private:
	const GuessResult answerGuessResult{3,0};
	string question;
};