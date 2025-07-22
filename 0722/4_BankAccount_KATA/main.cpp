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

	//wow... �� �κ� �߿�. 
	//Fixtrue���� TEST���� AccountFixture���� Account ��ü�� ��������� ���̴�.
	balanceCheck(9400); 
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}