#include "similarity.cpp"
#include "gmock/gmock.h"

using namespace testing;

class SimilarityFixture: public Test{
public:
	Similarity similarity;
	void validCheck(double expectedLengthScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedLengthScore, similarity.getLengthScore(str1, str2));
	}
};

TEST_F(SimilarityFixture, LengthSame) {
	validCheck(60.0, "ABC", "GHI");
}

TEST_F(SimilarityFixture, LengthX2) {
	validCheck(0.0, "ABC", "GHIDEF");
}

TEST_F(SimilarityFixture, LengthX2Over) {
	validCheck(0.0, "ABC", "GHIDEFABC");
}

TEST_F(SimilarityFixture, LengthPartScore1) {
	validCheck(36.0, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, LengthPartScore2) {
	validCheck(7.0*60/9, "ABCDEFG", "ABCDEFGHI");
}

