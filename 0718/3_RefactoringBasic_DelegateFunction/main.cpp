#include <iostream>
#include "gmock/gmock.h"
using namespace std;

int sumFrom1to100() {
	int result = 0;
	for(int num = 1; num <= 100; num++) {
		result += num;
	}
	return result;
}

int func() {
	return sumFrom1to100() * sumFrom1to100();
}

int rangedSum(int a, int b) {
	return 0;
}

TEST(test, sumFrom1to100) {
	int ret = sumFrom1to100();
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