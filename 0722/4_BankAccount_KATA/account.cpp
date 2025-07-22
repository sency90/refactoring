#pragma once
class Account {
public:
	Account(int balance) : balance(balance) {}

	int getBalance() const {
		return balance;
	}

	void deposit(int money) {
		balance += money;
	}

	void withdraw(int money) {
		balance -= money;
	}

private:
	int balance;
};
