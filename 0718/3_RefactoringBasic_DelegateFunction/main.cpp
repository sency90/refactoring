#include <iostream>
#include "gmock/gmock.h"
using namespace std;

int rangedSum(int b, int e) {
	return (e)*(e+1)/2 -(b-1)*b/2;
}

int func() {
	return rangedSum(1,100) * rangedSum(1,100);
}

TEST(test, sumFrom1to100) {
	int ret = rangedSum(1,100);
	EXPECT_EQ(5050, ret);
}

TEST(test, func) {
	int ret = func();
	EXPECT_EQ(5050 * 5050, ret);
}

int main() {
	testing::InitGoogleTest();
	testing::InitGoogleMock();

	return RUN_ALL_TESTS();
}