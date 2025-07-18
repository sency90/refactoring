#include "gmock/gmock.h"
#include "customer.cpp"

using namespace testing;

namespace {
	const std::string DUMMY_NAME("NAME_NOT_IMPORTANT");
	const std::string DUMMY_TITLE("TITLE_NOT_IMPORTANT");
};

class CustomerTestFixture: public Test{
public:
	Customer customer;
	CustomerTestFixture(): customer(string(DUMMY_NAME)) {}

	Rental getRentalFor(int daysRented, int priceCode) {
		Movie movie{string(DUMMY_TITLE), priceCode};
		return Rental{movie, daysRented};
	}

};

TEST_F(CustomerTestFixture, StatementForNoRental) {
	string statement = customer.statement();

	//assert
	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"Amount owed is 0.0\n"}
		+ string{"You earned 0 frequent renter points"}
	);
}

TEST_F(CustomerTestFixture, StatementForRegularMovieRentalForLessThan3Days) {
	Rental rental = getRentalFor(2, Movie::REGULAR);
	customer.addRental(rental);

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t2.0\n"}
		+ string{"Amount owed is 2.0\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}


TEST_F(CustomerTestFixture, StatementForRegularMovieRentalForMoreThan2Days) {
	Rental rental = getRentalFor(3, Movie::REGULAR);
	customer.addRental(rental);

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.5\n"}
		+ string{"Amount owed is 3.5\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST_F(CustomerTestFixture, StatementForNewReleaseMovie) {
	Rental rental = getRentalFor(3, Movie::CHILDREN);
	customer.addRental(rental);

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t1.5\n"}
		+ string{"Amount owed is 1.5\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST_F(CustomerTestFixture, StatementForChildrenMovieRentalMoreThan3Days) {
	// arrange
	Rental rental = getRentalFor(4, Movie::CHILDREN);
	customer.addRental(rental);

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+ string{"Amount owed is 3.0\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST_F(CustomerTestFixture, StatementForNewReleaseMovieRentalMoreThan1Day) {
	// arrange
	Rental rental = getRentalFor(2, Movie::NEW_RELEASE);
	customer.addRental(rental);

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t6.0\n"}
		+ string{"Amount owed is 6.0\n"}
		+ string{"You earned 2 frequent renter points"}
	);
}

TEST_F(CustomerTestFixture, StatementForFewMovieRentals) {
	// arrange
	customer.addRental(getRentalFor(1, Movie::REGULAR));
	customer.addRental(getRentalFor(4, Movie::NEW_RELEASE));
	customer.addRental(getRentalFor(4, Movie::CHILDREN));

	EXPECT_EQ(customer.statement(), ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t2.0\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t12.0\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+ string{"Amount owed is 17.0\n"}
		+ string{"You earned 4 frequent renter points"}
	);
}
