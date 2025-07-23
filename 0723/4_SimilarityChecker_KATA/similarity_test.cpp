#include "similarity.cpp"
#include "gmock/gmock.h"

using namespace testing;

class SimilarityFixture: public Test{
public:
	Similarity similarity;
	void validCheck(int expectedLenthScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedLenthScore, similarity.getLengthScore(str1, str2));
	}
};

TEST_F(SimilarityFixture, LengthSame) {
	validCheck(60, "ABC", "GHI");
}

