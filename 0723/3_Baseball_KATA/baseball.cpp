#include <stdexcept>
#include <string>
#include <cctype>
#include <iostream>
using namespace std;

struct GuessResult {
public:
	bool isSolved;
	int strikes;
	int balls;

public:
	GuessResult():isSolved(false), strikes(0), balls(0) {}
	GuessResult(bool isSolved, int strikes, int balls):isSolved(isSolved), strikes(strikes), balls(balls) {}
	bool operator==(const GuessResult& rhs) const {
		return isSolved == rhs.isSolved && strikes == rhs.strikes && balls == rhs.balls;
	}

	bool getIsSolved() const {
		return isSolved;
	}
	int getStrikes() const {
		return strikes;
	}
	int getBalls() const {
		return balls;
	}

	void countStrike() {
		strikes++;
		if(strikes==3) {
			isSolved = true;
		}
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
			return {true, 3, 0};
		}
		GuessResult guessResult;
		for(int i=0; i<question.size(); i++) {
			for(int j=0; j<guessNumber.size(); j++) {
				if(question[i] == guessNumber[j]) {
					if(i == j) {
						guessResult.countStrike();
						break;
					} else {
						guessResult.countBall();
						break;
					}
				}
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
	string question;
};