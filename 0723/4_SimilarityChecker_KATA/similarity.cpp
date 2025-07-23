#include <string>
#include <cstring>
#include <algorithm>

namespace {
	constexpr int LENGTH_PERFECT_SCORE = 60;
	constexpr int ZERO_SCORE = 0;
	constexpr int UNREACHABLE_CODE = -1;
	
}

class Similarity {
public:
	int getLengthScore(const std::string & str1, const std::string & str2) {
		if(str1.size() == str2.size()) return LENGTH_PERFECT_SCORE;
		int len1 = str1.size(), len2 = str2.size();
		int bigLen = std::max(len1,len2);
		int smallLen = std::min(len1,len2);
		if(bigLen >= 2*smallLen) return ZERO_SCORE;

		return smallLen*60/bigLen;
	}
};