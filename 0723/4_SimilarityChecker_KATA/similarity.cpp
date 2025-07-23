#include <string>
#include <cstring>
#include <algorithm>

namespace {
	constexpr int LENGTH_PERFECT_SCORE = 60;
	
}

class Similarity {
public:
	int getLengthScore(const std::string & str1, const std::string & str2) {
		if(str1.size() == str2.size()) return LENGTH_PERFECT_SCORE;
	}
};