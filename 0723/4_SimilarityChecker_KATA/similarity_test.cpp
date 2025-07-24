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
	void checkLengthScore(double expectedLengthScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedLengthScore, similarity.getLengthScore(str1, str2));
	}
	void checkAlphaScore(double expectedAlphaScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedAlphaScore, similarity.getAlphaScore(str1, str2));
	}
	void checkAlphaScoreNotEqualCase(double expectedAlphaScore, const std::string & str1, const std::string & str2) {
		EXPECT_NE(expectedAlphaScore, similarity.getAlphaScore(str1, str2));
	}
	void checkTotalScore(double expectedScore, const std::string & str1, const std::string & str2) {
		EXPECT_EQ(expectedScore, similarity.getScore(str1, str2));
	}
	void checkAlphaScoreThorwsException(const std::string & str1, const std::string & str2) {
		EXPECT_THROW(similarity.getAlphaScore(str1, str2), std::invalid_argument);
	}
};

TEST_F(SimilarityFixture, LengthSame) {
	checkLengthScore(LENGTH_PERFECT_SCORE, "ABC", "GHI");
}

TEST_F(SimilarityFixture, LengthX2) {
	checkLengthScore(ZERO_SCORE, "ABC", "GHIDEF");
}

TEST_F(SimilarityFixture, LengthX2Over) {
	checkLengthScore(ZERO_SCORE, "ABC", "GHIDEFABC");
}

TEST_F(SimilarityFixture, LengthPartialScore1) {
	checkLengthScore(20.0, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, LengthPartialScore2) {
	checkLengthScore((2*7.0-9)*LENGTH_PERFECT_SCORE/7, "ABCDEFG", "ABCDEFGHI");
}

TEST_F(SimilarityFixture, AlphaSame1) {
	checkAlphaScore(ALPHA_PERFECT_SCORE, "ABC", "ABC");
}

TEST_F(SimilarityFixture, AlphaTotallyDifferent) {
	checkAlphaScore(ZERO_SCORE, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase1) {
	checkAlphaScoreThorwsException("ABC", "aBC");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase2) {
	checkAlphaScoreThorwsException("aBC", "ABC");
}

TEST_F(SimilarityFixture, AlphaNoCapitalCase3) {
	checkAlphaScoreThorwsException("d12", "d12");
}

TEST_F(SimilarityFixture, AlphaSame2) {
	checkAlphaScore(ALPHA_PERFECT_SCORE, "ABCD", "ACDB");
}

TEST_F(SimilarityFixture, AlphaSame3) {
	checkAlphaScore(ALPHA_PERFECT_SCORE, "ABCD", "ACDBA");
}

TEST_F(SimilarityFixture, AlphaPartialScoreForFloatingPointPrecision1) {
	checkAlphaScore(4.0*ALPHA_PERFECT_SCORE/7.0, "ABCDEFGA", "ACDBA");
}

TEST_F(SimilarityFixture, AlphaPartialScoreForFloatingPointPrecision2) {
	checkAlphaScoreNotEqualCase(4.0/7.0*ALPHA_PERFECT_SCORE, "ABCDEFGA", "ACDBA");
}

TEST_F(SimilarityFixture, LengthAndAlphaCase1) {
	checkTotalScore(LENGTH_PERFECT_SCORE + ALPHA_PERFECT_SCORE, "ABC", "ABC");
}

TEST_F(SimilarityFixture, LengthAndAlphaCase2) {
	checkTotalScore((2*3.0-5)*LENGTH_PERFECT_SCORE/3+ ZERO_SCORE, "ABC", "DEFGH");
}

TEST_F(SimilarityFixture, LengthAndAlphaCase3) {
	checkTotalScore((2*8.0-10)*LENGTH_PERFECT_SCORE/8 + 7.0*ALPHA_PERFECT_SCORE/9.0, "ABCDAEFG", "ABCDEFGHIA");
}
