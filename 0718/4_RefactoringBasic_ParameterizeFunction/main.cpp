#include <iostream>
#include "gmock/gmock.h"

#include <algorithm> 

class TaxCalculator {
public:
	enum KindOf {
		LOWER, MIDDLE, UPPER
	};

	double calculateTax(double income) {
		double tax = 0;
		tax += whichBracket(income, LOWER) * 0.1;
		tax += whichBracket(income, MIDDLE) * 0.2;
		tax += whichBracket(income, UPPER) * 0.3;
		return tax;
	}

private:
	double whichBracket(double income, KindOf kindOf) {
		if(kindOf == LOWER) return std::min(income, 30000.0);
		else if(kindOf == MIDDLE) return (income > 30000) ? std::min(income, 100000.0) - 30000 : 0;
		else if(kindOf == UPPER) return (income > 100000) ? income - 100000 : 0;
	}
};

TEST(TS, TC1) {
	TaxCalculator calc;
	EXPECT_EQ(calc.calculateTax(15000), 1500);
}

TEST(TS, TC2) {
	TaxCalculator calc;
	EXPECT_EQ(calc.calculateTax(31000), 3200);
}

TEST(TS, TC3) {
	TaxCalculator calc;
	EXPECT_EQ(calc.calculateTax(100200), 17060);
}

int main() {
	testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}