#include "gmock/gmock.h"
#include "cal.cpp"

using namespace testing;

class MockCal : public Cal{
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
};

TEST(TS, TC1)
{
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}