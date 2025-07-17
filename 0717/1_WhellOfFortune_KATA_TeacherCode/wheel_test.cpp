#include "gmock/gmock.h"
#include "Wheel.cpp"

using std::vector;
using std::string;

TEST(WheelOfFortune, Price1) {
	vector<string> strs = { "BUILDLEV", "EATREALROBOT" };
	string userdata = "ERABCDFGHIJKLMNOPQSTUVWXYZ";
	Wheel app;

	int expected = 6500;

	int actual = app.getPrice(strs, userdata);
	EXPECT_EQ(expected, actual);
}

TEST(WheelOfFortune, Price2) {
	vector<string> strs = { "ABS", "ABS", "AAAAAKBA" };
	string userdata = "XASBKQDJHMNPTLVUCGEWFORIYZ";
	Wheel app;

	int expected = 9500;

	int actual = app.getPrice(strs, userdata);
	EXPECT_EQ(expected, actual);
}

TEST(WheelOfFortune, Price3) {
    Wheel app;
    vector<string> strs = { "ABXCVS", "ABS", "TEWRAAA"};
    string userdata = "LVXMNPTIKQASBDUCGEWFORJHYZ";

    int actual = app.getPrice(strs, userdata);

    EXPECT_EQ(6400, actual);
}
