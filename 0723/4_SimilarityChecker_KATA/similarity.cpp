#include <string>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <cctype>

namespace {
	constexpr double LENGTH_PERFECT_SCORE = 60.0;
	constexpr double ALPHA_PERFECT_SCORE = 40.0;
	constexpr double ZERO_SCORE = 0.0;
	constexpr bool ALL_CAPITAL = true;
	constexpr bool NOT_ALL_CAPITAL = false;
}

class Similarity {
public:
	double getLengthScore(const std::string & str1, const std::string & str2) {
		if(str1.size() == str2.size()) return LENGTH_PERFECT_SCORE;
		int len1 = str1.size();
		int len2 = str2.size();
		int bigLen = std::max(len1,len2);
		int smallLen = std::min(len1,len2);
		if(bigLen >= 2*smallLen) return ZERO_SCORE;

		return static_cast<double>(smallLen)*LENGTH_PERFECT_SCORE/bigLen;
	}

	bool isAllCapital(const std::string & str) {
		for(char ch: str) {
			if(false == isalpha(ch)) {
				return NOT_ALL_CAPITAL;
			}
			if(false == isupper(ch)) {
				return NOT_ALL_CAPITAL;
			}
		}
		return ALL_CAPITAL;
	}

	double getAplhaScore(const std::string & str1, const std::string & str2) {
		if(NOT_ALL_CAPITAL == isAllCapital(str1) || NOT_ALL_CAPITAL == isAllCapital(str2)) {
			throw std::invalid_argument("Input must be all capital letters.");
		}
		if(str1 == str2) return ALPHA_PERFECT_SCORE; 
		return ZERO_SCORE;
	}
};