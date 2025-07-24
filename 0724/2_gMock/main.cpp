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
	MockCal mockCal; //��ü ����

	//�ൿ ���� (Behavior Verification)
	//Act�� �� �� 3�� ȣ��Ǿ�� Pass
	//�� EXPECT_CALL�� mockCal.getSum()�� ȣ���ϱ� ���� Setting�Ǿ�� �Ѵ�.
	EXPECT_CALL(mockCal, getSum(10,20)).Times(3);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(10,20);
	int t3 = mockCal.getSum(10,20);
}

TEST(TS, TC2) {
	MockCal mockCal; //��ü ����

	//Matcher�� ���� �� �� �ִ�.
	//_�� Wild Card�� ���Ѵ�.
	EXPECT_CALL(mockCal, getSum(_,Gt(5))).Times(3);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(1,10);
	int t3 = mockCal.getSum(3,6);
}

TEST(TS, TC3) {
	MockCal mockCal; //��ü ����

	//2���� ȣ��Ǿ�� ���� �����ϴ� ���̴�.
	EXPECT_CALL(mockCal, getSum(_,_)).Times(2);

	int t1 = mockCal.getSum(10,20);
	int t2 = mockCal.getSum(1,10);
}

TEST(TS, TC4) {
	MockCal mockCal;
	//mockCal ��ü�� ��¥��!
	//return���� �׳� 0�̴�. getSum()�� ��¥�� �����ϴ°� �ƴϴ�.
	EXPECT_EQ(mockCal.getSum(1,2), 0);
}

TEST(TS, TC5) {
	MockCal mockCal;

	//Stub: A�� ������ ������ B�� ���ϵǾ�� ���� Setting
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