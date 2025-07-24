#include "gmock/gmock.h"
#include "cal.cpp"

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

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}