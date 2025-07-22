#include <cstdio>
#include <iostream>
#include "gmock/gmock.h"
#include "cal.cpp"

TEST(TS, TC1) {
	Cal app;
	int ret = app.getMinus(10,2);
	EXPECT_EQ(8, ret);
}

TEST(TS, TC) {
	Cal app;
	int ret = app.getMinus(5,2);
	EXPECT_EQ(3, ret);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}