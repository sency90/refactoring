#pragma once
#include <cstdio>
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

	void applyCompoundInterest(double rate) {
		balance += static_cast<int>(balance * rate / 100.0);
	}

	void setCompoundInterest(double rate) {
		this->rate = rate;
	}

	void setRate(double rate) {
		this->rate = rate;

	}
	double getRate() const {
		return rate;
	}
	void applyRate() {
		applyCompoundInterest(rate);
	}
	int expectBalanceWithNYearRate(int year, double rate) {
		if(year==0) return balance;
		int newBalance = expectBalanceWithNYearRate(year-1, rate);
		newBalance += static_cast<int>(newBalance * rate / 100.0);
		return newBalance;
	}


private:
	int balance;
	double rate;
};
