#pragma once
#include <string>
#include <vector>

class SumChecker{
public:
	bool ValidateSumEquation(const std::string & str);


private:
	char err_msg[1024];
	const int NA = -1;
	std::vector<std::string> __Split(const std::string & str);
	bool __CheckSum(const std::vector<std::string> & str_list);
	bool __IsAllDigit(const std::string & str);
};
