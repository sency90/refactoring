#include <stdexcept>
#include <string>
#include <cctype>
using namespace std;

class Baseball {
public:
	void guess(const string& guessNumber) {
		if(guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for(char ch : guessNumber) {
			if(false == isdigit(ch)) {
				throw invalid_argument("Must be number");
			}
		}

		if(guessNumber[0] == guessNumber[1]
		   || guessNumber[0] == guessNumber[2]
		   || guessNumber[1] == guessNumber[2]) {
			throw invalid_argument("Must not have the same number");
		}
	}
};