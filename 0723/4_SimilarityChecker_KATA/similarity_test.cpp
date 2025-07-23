#include "similarity.cpp"
#include "gmock/gmock.h"
#include <stdexcept>

using namespace testing;

namespace {
	extern const double LENGTH_PERFECT_SCORE;
	extern const double ALPHA_PERFECT_SCORE;
	extern const double ZERO_SCORE;
}

class SimilarityFixture: public Test{
public:
	Similarity similarity;
	void validLengthCheck(double expectedLengthScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedLengthScore, similarity.getLengthScore(str1, str2));
	}
	void validAlphaCheck(double expectedAlphaScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedAlphaScore, similarity.getAlphaScore(str1, str2));
	}
	void validAlphaCheckThrowsException(const std::string & str1, const std::string & str2) {
		EXPECT_THROW(similarity.getAlphaScore(str1, str2), std::invalid_argument);
	}
};

TEST_F(SimilarityFixture, LengthSame) {
	validLengthCheck(LENGTH_PERFECT_SCORE, "ABC", "GHI");
}

TEST_F(SimilarityFixture, LengthX2) {
	validLengthCheck(ZERO_SCORE, "ABC", "GHIDEF");
}

TEST_F(SimilarityFixture, LengthX2Over) {
	validLengthCheck(ZERO_SCORE, "ABC", "GHIDEFABC");
}

TEST_F(SimilarityFixture, LengthPartialScore1) {
	validLengthCheck(36.0, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, LengthPartialScore2) {
	validLengthCheck(7.0*LENGTH_PERFECT_SCORE/9, "ABCDEFG", "ABCDEFGHI");
}

TEST_F(SimilarityFixture, AlphaSame1) {
	validAlphaCheck(ALPHA_PERFECT_SCORE, "ABC", "ABC");
}

TEST_F(SimilarityFixture, AlphaTotallyDifferent) {
	validAlphaCheck(ZERO_SCORE, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase1) {
	validAlphaCheckThrowsException("ABC", "aBC");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase2) {
	validAlphaCheckThrowsException("aBC", "ABC");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase3) {
	validAlphaCheckThrowsException("d12", "d12");
}

TEST_F(SimilarityFixture, AlphaSame2) {
	validAlphaCheck(ALPHA_PERFECT_SCORE, "ABCD", "ACDB");
}

TEST_F(SimilarityFixture, AlphaSame3) {
	validAlphaCheck(ALPHA_PERFECT_SCORE, "ABCD", "ACDBA");
}

TEST_F(SimilarityFixture, AlphaPartialScore) {
	validAlphaCheck(4.0*ALPHA_PERFECT_SCORE/7.0, "ABCDEFG", "ACDBA");
}
