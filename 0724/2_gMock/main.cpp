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
	//이 EXPECT_CALL은 mockCal.getSum()을 호출하기 전에 Setting되어야 한다.
	EXPECT_CALL(mockCal, getSum(10,20)).Times(3);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(10,20);
	int t3 = mockCal.getSum(10,20);
}

TEST(TS, TC2) {
	MockCal mockCal; //객체 생성

	//Matcher도 같이 쓸 수 있다.
	//_는 Wild Card를 뜻한다.
	EXPECT_CALL(mockCal, getSum(_,Gt(5))).Times(3);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(1,10);
	int t3 = mockCal.getSum(3,6);
}

TEST(TS, TC3) {
	MockCal mockCal; //객체 생성

	//2번만 호출되어야 함을 검증하는 것이다.
	EXPECT_CALL(mockCal, getSum(_,_)).Times(2);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(1,10);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}