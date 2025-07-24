#include "gmock/gmock.h"
#include "cal.cpp"

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}