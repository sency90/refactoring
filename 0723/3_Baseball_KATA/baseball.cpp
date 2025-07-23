#include <stdexcept>
#include <string>
#include <cctype>
using namespace std;

class Baseball {
public:
	void guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
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
};