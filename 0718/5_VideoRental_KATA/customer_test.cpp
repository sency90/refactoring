#include "gmock/gmock.h"
#include "customer.cpp"

TEST(CustomerTest, StatementForNoRental) {
	//arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};

	//act
	string statement = customer.statement();

	//assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"Amount owed is 0.0\n"}
		+ string{"You earned 0 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForRegularMovieRentalForLessThan3Days) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::REGULAR};
	int daysRented = 2;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t2.0\n"}
		+ string{"Amount owed is 2.0\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}


TEST(CustomerTest, StatementForRegularMovieRentalForMoreThan2Days) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::REGULAR};
	int daysRented = 3;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.5\n"}
		+ string{"Amount owed is 3.5\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForNewReleaseMovie) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::NEW_RELEASE};
	int daysRented = 1;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+ string{"Amount owed is 3.0\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForChildrenMovieRentalMoreThan2Days) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::CHILDREN};
	int daysRented = 3;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t1.5\n"}
		+ string{"Amount owed is 1.5\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForChildrenMovieRentalMoreThan3Days) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::CHILDREN};
	int daysRented = 4;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+ string{"Amount owed is 3.0\n"}
		+ string{"You earned 1 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForNewReleaseMovieRentalMoreThan1Day) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie movie{string{"TITLE_NOT_IMPORTANT"}, Movie::NEW_RELEASE};
	int daysRented = 2;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t6.0\n"}
		+ string{"Amount owed is 6.0\n"}
		+ string{"You earned 2 frequent renter points"}
	);
}

TEST(CustomerTest, StatementForFewMovieRentals) {
	// arrange
	Customer customer{string{"NAME_NOT_IMPORTANT"}};
	Movie regularMovie{string{"TITLE_NOT_IMPORTANT"}, Movie::REGULAR};
	Movie newReleaseMovie{string{"TITLE_NOT_IMPORTANT"}, Movie::NEW_RELEASE};
	Movie childrenMovie{string{"TITLE_NOT_IMPORTANT"}, Movie::CHILDREN};
	customer.addRental(Rental{regularMovie, 1});
	customer.addRental(Rental{newReleaseMovie, 4});
	customer.addRental(Rental{childrenMovie, 4});

	// act
	string statement = customer.statement();

	// assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t2.0\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t12.0\n"}
		+ string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+ string{"Amount owed is 17.0\n"}
		+ string{"You earned 4 frequent renter points"}
	);
}