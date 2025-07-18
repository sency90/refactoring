#include "gmock/gmock.h"
#include "customer.cpp"

#if 0
TEST(CustomerTest, SampleTest) {
	Customer customer{string{ "Bob" }};

	customer.addRental(Rental{Movie{ string{ "Jaws" }, Movie::REGULAR }, 2});
	customer.addRental(Rental{Movie{ string{ "Golden Eye" }, Movie::REGULAR }, 3});
	customer.addRental(Rental{Movie{ string{ "Short New" }, Movie::NEW_RELEASE }, 1});
	customer.addRental(Rental{Movie{ string{ "Long New" }, Movie::NEW_RELEASE }, 2});
	customer.addRental(Rental{Movie{ string{ "Bambi" }, Movie::CHILDREN }, 3});
	customer.addRental(Rental{Movie{ string{ "Toy Story" }, Movie::CHILDREN }, 4});

	string expected = "" +
		string{"Rental Record for Bob\n"} +
		string{"\tJaws\t2.0\n"} +
		string{"\tGolden Eye\t3.5\n"} +
		string{"\tShort New\t3.0\n"} +
		string{"\tLong New\t6.0\n"} +
		string{"\tBambi\t1.5\n"} +
		string{"\tToy Story\t3.0\n"} +
		string{"Amount owed is 19.0\n"} +
		string{"You earned 7 frequent renter points"};

	EXPECT_EQ(expected, customer.statement());
}
#endif

namespace {
	const string DUMMY_CUSTOMER_NAME = "NAME_NOT_IMPORTANT";
	const string DUMMY_MOVIE_NAME = "TITLE_NOT_IMPORTANT";
};

//Golden Master Test 1. Movie를 Rental하지 않은 경우 Test
TEST(CustomerTest, StatementForNoRental) {
	//arrange
	Customer customer{string{DUMMY_CUSTOMER_NAME}};

	//act
	string statement = customer.statement();

	//assert
	EXPECT_EQ(statement, ""
		+ string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+ string{"Amount owed is 0.0\n"}
		+ string{"You earned 0 frequent renter points"}
	);
}

//Golden Master Test2. Amount 계산 로직 Test - if조건 분기 경계값 Test
TEST(CustomerTest, StatementForRegularMovieRentalForLessThan2Days) {
	Customer customer{string{DUMMY_CUSTOMER_NAME}};
	Movie movie{string{DUMMY_MOVIE_NAME}, Movie::REGULAR};
	int daysRented = 1;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	string statement = customer.statement();

	EXPECT_EQ(statement, ""
		+string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+string{"\tTITLE_NOT_IMPORTANT\t2.0\n"}
		+string{"Amount owed is 2.0\n"}
		+string{"You earned 1 frequent renter points"}
	);
}

//Golden Master Test3. Amount 계산 로직 Test - if조건 분기 경계값 Test
TEST(CustomerTest, StatementForRegularMovieRentalForMoreThan3Days) {
	Customer customer{string{DUMMY_CUSTOMER_NAME}};
	Movie movie{string{DUMMY_MOVIE_NAME}, Movie::REGULAR};
	int daysRented = 3;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	string statement = customer.statement();

	EXPECT_EQ(statement, ""
		+string("Rental Record for NAME_NOT_IMPORTANT\n")
		+string("\tTITLE_NOT_IMPORTANT\t3.5\n")
		+string("Amount owed is 3.5\n")
		+string("You earned 1 frequent renter points")
	);
}

//Golden Master Test4. Amount 계산 로직 Test - New Release Movie
TEST(CustomerTest, StatementForNewReleaseMovie) {
	//arange
	Customer customer{string{DUMMY_CUSTOMER_NAME}};
	Movie movie{string{DUMMY_MOVIE_NAME}, Movie::NEW_RELEASE};
	int daysRented=1;
	Rental rental{movie, daysRented};
	customer.addRental(rental);

	//act
	string statement = customer.statement();

	//assert
	EXPECT_EQ(statement, ""
		+string{"Rental Record for NAME_NOT_IMPORTANT\n"}
		+string{"\tTITLE_NOT_IMPORTANT\t3.0\n"}
		+string{"Amount owed is 3.0\n"}
		+string{"You earned 1 frequent renter points"}
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
