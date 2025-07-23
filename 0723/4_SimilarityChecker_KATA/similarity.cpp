#include <string>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <unordered_map>

namespace {
	const double LENGTH_PERFECT_SCORE = 60.0;
	const double ALPHA_PERFECT_SCORE = 40.0;
	const double ZERO_SCORE = 0.0;
	const bool ALL_CAPITAL = true;
	const bool NOT_ALL_CAPITAL = false;
}

class Similarity {
public:
	double getScore(const std::string& str1, const std::string& str2) {
		return getLengthScore(str1, str2) + getAlphaScore(str1, str2);
	}

	double getLengthScore(const std::string& str1, const std::string& str2) {
		if(str1.size() == str2.size()) return LENGTH_PERFECT_SCORE;
		int len1 = static_cast<int>(str1.size());
		int len2 = static_cast<int>(str2.size());
		int bigLen = std::max(len1, len2);
		int smallLen = std::min(len1, len2);
		if(bigLen >= 2*smallLen) return ZERO_SCORE;

		return getLengthPartialScore(smallLen, bigLen);
	}

	double getAlphaScore(const std::string& str1, const std::string& str2) {
		assertAllUppercase(str1, str2);

		if(str1 == str2) return ALPHA_PERFECT_SCORE;
		else if(isTotallyDifferent(str1, str2)) return ZERO_SCORE;

		return getAlphaPartialScore(str1, str2);
	}

private:
	double getLengthPartialScore(int smallLen, int bigLen) {
		return static_cast<double>(2*smallLen-bigLen)*LENGTH_PERFECT_SCORE/smallLen;
	}

	bool isAllUpper(const std::string& str) {
		for(char ch: str) {
			if(false == isalpha(ch)) return NOT_ALL_CAPITAL;
			if(false == isupper(ch)) return NOT_ALL_CAPITAL;
		}
		return ALL_CAPITAL;
	}

	bool isTotallyDifferent(const std::string& str1, const std::string& str2) {
		for(char ch1: str1) {
			for(char ch2: str2) {
				if(ch1 == ch2) return false;
			}
		}
		return true;
	}

	void assertAllUppercase(const std::string& str1, const std::string& str2) {
		if(NOT_ALL_CAPITAL == isAllUpper(str1)) {
			throw std::invalid_argument("Input must be all capital letters.");
		}
		if(NOT_ALL_CAPITAL == isAllUpper(str2)) {
			throw std::invalid_argument("Input must be all capital letters.");
		}
	}

	double getAlphaPartialScore(const std::string& str1, const std::string& str2) {
		int sameCnt = getAlphaSameCnt(str1, str2);
		int totalCnt = getAlphaTotalCnt(str1, str2);

		return static_cast<double>(sameCnt) * ALPHA_PERFECT_SCORE / totalCnt;
	}

	int getAlphaSameCnt(const std::string& str1, const std::string& str2) {
		std::unordered_map<char, int>& str1CharCount = charCount[0];
		str1CharCount.clear();
		for(char ch : str1) str1CharCount[ch]++;

		std::unordered_map<char, int>& sameCharCount = charCount[1];
		sameCharCount.clear();
		for(char ch : str2) {
			if(str1CharCount.count(ch)>0) {
				sameCharCount[ch]++;
			}
		}

		return static_cast<int>(sameCharCount.size());
	}

	int getAlphaTotalCnt(const std::string& str1, const std::string& str2) {
		std::unordered_map<char, int>& totalCharCount = charCount[0];
		totalCharCount.clear();
		for(char ch : str1) totalCharCount[ch]++;
		for(char ch : str2) totalCharCount[ch]++;
		return static_cast<int>(totalCharCount.size());
	}

private:
	std::unordered_map<char, int> charCount[2];
};
