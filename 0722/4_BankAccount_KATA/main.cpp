#include "gmock/gmock.h"
#include "account.cpp"

class AccountFixture : public ::testing::Test {
public:
	Account account{10000};

	void balanceCheck(int expected) {
		int actual = account.getBalance();
		EXPECT_EQ(expected, actual);
	}
};

TEST_F(AccountFixture, CreateAccountInit10000Won) {
	int actual = account.getBalance();
	balanceCheck(10000);
}

TEST_F(AccountFixture, Deposit) {
	account.deposit(500);
	int actual = account.getBalance();
	balanceCheck(10500);
}
TEST_F(AccountFixture, Withdraw) {
	account.withdraw(600);
	int actual = account.getBalance();

	//wow... 이 부분 중요. 
	//Fixtrue사용시 TEST마다 AccountFixture내의 Account 객체가 만들어지는 셈이다.
	balanceCheck(9400); 
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}