#include "similarity.cpp"
#include "gmock/gmock.h"

using namespace testing;

class SimilarityFixture: public Test{
public:
	Similarity similarity;
	void validLengthCheck(double expectedLengthScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedLengthScore, similarity.getLengthScore(str1, str2));
	}
	void validAplhaCheck(double expectedAlphaScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedAlphaScore, similarity.getAplhaScore(str1, str2));
	}
};

TEST_F(SimilarityFixture, LengthSame) {
	validLengthCheck(60.0, "ABC", "GHI");
}

TEST_F(SimilarityFixture, LengthX2) {
	validLengthCheck(0.0, "ABC", "GHIDEF");
}

TEST_F(SimilarityFixture, LengthX2Over) {
	validLengthCheck(0.0, "ABC", "GHIDEFABC");
}

TEST_F(SimilarityFixture, LengthPartScore1) {
	validLengthCheck(36.0, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, LengthPartScore2) {
	validLengthCheck(7.0*60/9, "ABCDEFG", "ABCDEFGHI");
}


TEST_F(SimilarityFixture, AlphaSame) {
	validAplhaCheck(40.0, "ABC", "ABC");
}

TEST_F(SimilarityFixture, AlphaTotallyDifferent) {
	validAplhaCheck(0.0, "ABC", "DEFGH");
}
