#include "SumChecker.h"
#include <string>
#include "gmock/gmock.h"

using std::string;

int main()
{
	//25+61=100
	//1 ~ 5자리수 덧셈 수식이 맞는지 확인하는 프로그램
	//띄어쓰기 없음

	string str = "25+61=86"; //PASS
	//string str = "12345+12345=24690"; //PASS
	//string str = "12345+=12345"; // ERROR
	//string str = "5++5=10"; //ERROR
	//string str = "10000+1=10002"; //FAIL

	//SumChecker sum_checker;

	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
