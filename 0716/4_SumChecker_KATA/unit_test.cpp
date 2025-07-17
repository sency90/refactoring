#include "gmock/gmock.h"
#include "SumChecker.h"
using namespace testing;

class SumCheckerFixture: public Test{
public:
	SumChecker sum_checker;
	void expect_eq(const std::string & str,bool expected_val) {
		EXPECT_EQ(sum_checker.ValidateSumEquation(str),expected_val);
	}
};
TEST_F(SumCheckerFixture,TC1) {
	expect_eq("25+61=86",true);
}
TEST_F(SumCheckerFixture,TC2) {
	expect_eq("5=2+3",false);
}
TEST_F(SumCheckerFixture,TC3) {
	expect_eq("1=2+3",false);
}
TEST_F(SumCheckerFixture,TC4) {
	expect_eq("1000+=1000",false);
}
TEST_F(SumCheckerFixture,TC5) {
	expect_eq("1000+ =1000",false);
}
TEST_F(SumCheckerFixture,TC6) {
	expect_eq("1++=1",false);
}
TEST_F(SumCheckerFixture,TC7) {
	expect_eq("1+==1",false);
}

