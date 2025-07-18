#include <iostream>
#include "gmock/gmock.h"

#include <algorithm> 

class TaxCalculator {
public:
	double calculateTax(double income) {
		double tax = 0;
		tax += lowerBracket(income) * 0.1;
		tax += middleBracket(income) * 0.2;
		tax += upperBracket(income) * 0.3;
		return tax;
	}

private:
	double lowerBracket(double income) {
		return std::min(income, 30000.0);
	}

	double middleBracket(double income) {
		return (income > 30000) ? std::min(income, 100000.0) - 30000 : 0;
	}

	double upperBracket(double income) {
		return (income > 100000) ? income - 100000 : 0;
	}
};

TEST(a, b) {
	TaxCalculator calc;
	EXPECT_EQ(calc.calculateTax(15000), 1500);
	EXPECT_EQ(calc.calculateTax(31000), 3200);
	EXPECT_EQ(calc.calculateTax(100200), 17060);
}

int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}