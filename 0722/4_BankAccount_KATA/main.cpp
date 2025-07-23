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


TEST_F(AccountFixture, applyCompoundInterest5Percent) {
	account.applyCompoundInterest(5);
	int actual = account.getBalance();
	balanceCheck(10500);
}

TEST_F(AccountFixture, SetRate) {
	const double rate = 10.1;
	account.setRate(rate);
	int actual = account.getBalance();
	balanceCheck(10000);
	double out_rate = account.getRate();
	EXPECT_EQ(rate, out_rate);
}

TEST_F(AccountFixture, ApplyRate) {
	const double rate = 10.1;
	account.setRate(rate);
	account.applyRate();
	balanceCheck(11010);
}

TEST_F(AccountFixture, ExpectNYearRate) {
	const int year = 10;
	const double rate = 10.1;
	balanceCheck(10000);
	double expected_balance = account.expectBalanceWithNYearRate(year, rate);
	EXPECT_EQ(expected_balance, 26167);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}