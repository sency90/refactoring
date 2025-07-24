#include "gmock/gmock.h"
#include "cal.cpp"
#include <iostream>

using std::cout;
using namespace testing;

//MockInjection을 하지 않은 경우
TEST(TS, TC1NOMOCKINJECTION) {
	Bank bank;
	Cal cal{&bank};

	const int BANK_NOT_VERIFIED = -1;
	EXPECT_THAT(cal.getSum(1,2), BANK_NOT_VERIFIED);
}

class BankMock: public BankInterface{
public:
	MOCK_METHOD(bool, verify, (), (override));
};

TEST(TS, TC2MOCKINJECTION) {
	BankMock bankMock;
	
	EXPECT_CALL(bankMock, verify)
		.WillRepeatedly(Return(true));

	Cal cal{&bankMock};
	cout << cal.getSum(1,2) << "\n";
	cout << cal.getSum(1,2) << "\n";
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}