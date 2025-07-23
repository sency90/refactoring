#include <string>
#include <cstring>
#include <algorithm>

namespace {
	constexpr int LENGTH_PERFECT_SCORE = 60;
	constexpr int ZERO_SCORE = 0;
	
}

class Similarity {
public:
	int getLengthScore(const std::string & str1, const std::string & str2) {
		if(str1.size() == str2.size()) return LENGTH_PERFECT_SCORE;
		int len1 = str1.size();
		int len2 = str2.size();
		if(len1 > len2) std::swap(len1, len2);
		if(len1*2 <= len2) return ZERO_SCORE;
		else return -1;
	}
};