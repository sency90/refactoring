#include <vector>
#include <string>
#include "movie.cpp"
#include "rental.cpp"

using std::vector;
using std::string;

class Customer {
private:
	string name;
	vector<Rental> rentals;


public:
	Customer(const string& name) : name{name} {}

	void addRental(Rental arg) {
		rentals.push_back(arg);
	}

	string getName() const {
		return name;
	}

	string statement() {
		string result = makeHeaderForStatement();

		double totalAmount = 0;
		for(Rental rental : rentals) {
			//determine amounts for rental
			double thisAmount = getCharge(rental);
			totalAmount += thisAmount;

			// show figures for this rental
			result += makeBodyForStatement(rental, thisAmount);
		}

		int frequentRenterPoints = getFrequentRentalPoints();

		// add footer lines
		result += makeFooterForStatement(totalAmount, frequentRenterPoints);

		return result;
	}

	std::string makeHeaderForStatement() {
		 return std::string("Rental Record for ") + getName() + "\n";
	}

	std::string makeBodyForStatement(Rental &rental, double thisAmount) {
		return std::string("\t") + rental.getMovie().getTitle() + "\t" + roundDoubleToString(thisAmount) + "\n";
	}

	std::string makeFooterForStatement(double totalAmount, int frequentRenterPoints) {
		std::string result;
		result += "Amount owed is " + roundDoubleToString(totalAmount) + "\n";
		result += "You earned " + std::to_string(frequentRenterPoints) + " frequent renter points";
		return result;
	}

	int getFrequentRentalPoints() {
		int result=0;
		for(Rental rental : rentals) {
			// add bonus for a two day new release rental
			if(rental.getMovie().getPriceCode() == Movie::NEW_RELEASE && rental.getDaysRented() > 1) {
				result+=2;
			}
			else { //normal case
				result++; // add frequent renter points
			}
		}
		return result;
	}

	double getCharge(Rental &rental) {
		switch(rental.getMovie().getPriceCode()) {
		case Movie::REGULAR:
			return getRegularCharge(rental);
		case Movie::NEW_RELEASE:
			return getNewReleaseCharge(rental);
		case Movie::CHILDREN:
			return getChildrenCharge(rental);
		default:
			return 0.0;
		}
	}
	double getChildrenCharge(Rental & rental) {
		double result = 1.5;
		if(rental.getDaysRented() > 3) {
			result += (rental.getDaysRented() - 3) * 1.5;
		}
		return result;
	}
	double getNewReleaseCharge(Rental & rental) {
		return rental.getDaysRented() * 3.0;
	}
	double getRegularCharge(Rental & rental) {
		double result = 2;
		if(rental.getDaysRented() > 2) {
			result += (rental.getDaysRented() - 2) * 1.5;
		}
		return result;
	}

	string roundDoubleToString(double tar) {
		char buf[20] = {0};
		sprintf_s(buf, sizeof(buf), "%.1f", tar);
		return string{buf};
	}
};
