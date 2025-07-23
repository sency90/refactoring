#include <string>
#include <cstring>
#include <algorithm>

namespace {
	constexpr double LENGTH_PERFECT_SCORE = 60.0;
	constexpr double ZERO_SCORE = 0.0;
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
};