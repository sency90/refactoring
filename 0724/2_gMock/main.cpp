#include "gmock/gmock.h"
#include "cal.cpp"
#include <iostream>

using std::cout;
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

TEST(TS, TC4) {
	MockCal mockCal;
	//mockCal 객체는 가짜다!
	//return값은 그냥 0이다. getSum()을 진짜로 수행하는게 아니다.
	EXPECT_EQ(mockCal.getSum(1,2), 0);
}

TEST(TS, TC5) {
	MockCal mockCal;

	//Stub: A를 넣으면 무조건 B가 리턴되어야 함을 Setting
	EXPECT_CALL(mockCal, getSum(1,2)).WillRepeatedly(Return(100));

	cout << mockCal.getSum(1,2) << "\n";
}

TEST(TS, TC6) {
	MockCal mockCal;

	EXPECT_CALL(mockCal, getSum(1,2)).
		WillRepeatedly(Return(100));
	
	EXPECT_CALL(mockCal, getSum(5,6))
		.WillOnce(Return(1))
		.WillOnce(Return(2))
		.WillRepeatedly(Return(50));

	cout << mockCal.getSum(1,2) << "\n";
	cout << mockCal.getSum(5,6) << "\n";
	cout << mockCal.getSum(5,6) << "\n";
	cout << mockCal.getSum(5,6) << "\n";
	cout << mockCal.getSum(5,6) << "\n";
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}