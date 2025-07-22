#include <cstdio>
#include <iostream>
#include "gmock/gmock.h"
#include "fibo.cpp"

TEST(FiboTest, OrderTest) {
	std::vector<std::pair<int, int>> cases = {
		{0,0},
		{1,1},
		{2,1},
		{3,2}
	};
	for(auto tc : cases) {
		EXPECT_EQ(tc.second, Fibo().fibo(tc.first));
	}
	//EXPECT_EQ(0, Fibo().fibo(0));
	//EXPECT_EQ(1, Fibo().fibo(1));
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}