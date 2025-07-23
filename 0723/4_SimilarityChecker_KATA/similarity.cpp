#include <string>
#include <cstring>

class Similarity {
public:
	int getLengthScore(const std::string & str1, const std::string & str2) {
		if(str1.size() == str2.size()) return 60;
	}
};