#include "gmock/gmock.h"
#include "cal.cpp"

using namespace testing;

class MockCal : public Cal{
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
};

TEST(TS, TC1) {
	MockCal mockCal; //객체 생성

	//행동 검증 (Behavior Verification)
	//Act를 할 때 3번 호출되어야 Pass
	EXPECT_CALL(mockCal, getSum(10,20)).Times(3);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(10,20);
	int t3 = mockCal.getSum(10,20);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}