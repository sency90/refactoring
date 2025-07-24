#include "gmock/gmock.h"
#include <cstdio>
#include <vector>
#include <string>
using std::vector;
using std::string;
using namespace testing;

//Matcher를 써야 하는 이유:
//	1. 가독성있는 Assertion을 만들고 싶을 떄
//	2. 중복 코드를 줄이고, 복잡한 코드를 간결하게 만들고 싶을 때

TEST(TS, TC1) {
	int ret = 10;
	EXPECT_THAT(ret, Eq(10));
}
TEST(TS, TC2) {
	int ret = 10;
	EXPECT_THAT(ret, AnyOf(1, 2, 10));
}
TEST(TS, TC3) {
	int arr[] = {1, 2, 3, 4, 5};
	EXPECT_THAT(arr, Contains(3));
}
TEST(TS, TC4) {
	int x = 10;
	EXPECT_THAT(x, Gt(9));
}
TEST(TS, TC5) {
	int x = 10;
	EXPECT_THAT(x, Ge(10));
}
TEST(TS, TC6) {
	double pi = 3.14;
	EXPECT_THAT(pi, DoubleNear(3.1415, 0.1));
}
TEST(TS, TC7) {
	vector<int> arr = {1,4,2,5,9,15};
	EXPECT_THAT(arr, Contains(Ge(14)));
	EXPECT_THAT(arr, Not(Contains(8)));
}
TEST(TS, TC8) {
	string str = "aB13z";
	EXPECT_THAT(str, MatchesRegex("a.*z"));
}
TEST(TS, TC9) {
	string str = "LORD OF KFC ";
	EXPECT_THAT(str, StartsWith("LORD"));
	EXPECT_THAT(str, EndsWith(""));
}
class ElementManager {
public:
	vector<int> add1All(const vector<int>& arr) {
		vector<int> result;
		for(int num : arr) {
			num++;
			if(num==10) num=0;
			if(num==4) num=5;
			result.push_back(num);
		}
		return result;
	}
};
TEST(TSCHALLENGE, TC1) {
	ElementManager elementManager;
	vector<int> input = {1, 1, 1, 1};
	vector<int> expected = {2, 2, 2, 2};
	vector<int> output = elementManager.add1All(input);
	EXPECT_THAT(output, ContainerEq(expected));
}
TEST(TSCHALLENGE, TC2) {
	ElementManager elementManager;
	vector<int> input = {1, 2, 7, 8};
	vector<int> expected = {2, 3, 8, 9};
	vector<int> output = elementManager.add1All(input);
	EXPECT_THAT(output, ContainerEq(expected));
}
TEST(TSCHALLENGE, TC3) {
	ElementManager elementManager;
	vector<int> input = {3};
	vector<int> output = elementManager.add1All(input);
	EXPECT_THAT(output, Contains(5));
}
TEST(TSCHALLENGE, TC4) {
	ElementManager elementManager;
	vector<int> input = {11, 10, 9, 8};
	vector<int> expected = {12, 11, 0, 9};
	vector<int> output = elementManager.add1All(input);
	EXPECT_THAT(output, ContainerEq(expected));
}
int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}