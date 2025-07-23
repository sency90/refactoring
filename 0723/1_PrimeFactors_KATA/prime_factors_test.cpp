#include "gmock/gmock.h"
#include "prime_factors.cpp"
#include <vector>
using std::vector;
using namespace testing;

class PrimeFixture : public Test{
public:
	PrimeFactors prime_factor;
	vector<int> expected;
};

TEST_F(PrimeFixture, Of1) {
	expected = {};
	EXPECT_EQ(expected, prime_factor.of(1));
}

TEST_F(PrimeFixture, Of2) {
	expected = {2};
	EXPECT_EQ(expected, prime_factor.of(2));
}

