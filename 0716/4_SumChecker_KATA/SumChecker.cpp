#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <memory>
#include <sstream>
#include <stdexcept>
#include "SumChecker.h"
using namespace std;

bool SumChecker::ValidateSumEquation(const std::string & str) {
	try {
		std::vector<std::string> splited_str_list = __Split(str);
		return __CheckSum(splited_str_list);
	} catch(std::exception & ex) {
		printf("FAIL (EXCEPTION: %s)\n", ex.what());
		return false;
	}
}

bool SumChecker::__CheckSum(const std::vector<std::string> & str_list) {
	int num1 = stoi(str_list[0]);
	int num2 = stoi(str_list[1]);
	int num3 = stoi(str_list[2]);

	if(num1 + num2 == num3) {
		cout << "PASS\n";
		return true;
	}

	cout << "FAIL\n";
	return false;
}

std::vector<std::string> SumChecker::__Split(const std::string & str) {
	std::vector<std::string> ret;
	std::stringstream ss;
	std::string buf;

	ss.str(""); ss.clear();
	ss.str(str);
	std::getline(ss, buf, '+');

	if(false ==__IsAllDigit(buf)) {
		sprintf(err_msg, "ERR: valid chars are 0-9, +, = Only. (Line%d@%s)", __LINE__, __FILE__);
		throw std::exception(err_msg);
	}
	ret.emplace_back(buf);

	std::getline(ss, buf, '=');
	if(false ==__IsAllDigit(buf)) {
		sprintf(err_msg, "ERR: valid chars are 0-9, +, = Only. (Line%d@%s)", __LINE__, __FILE__);
		throw std::exception(err_msg);
	}
	ret.emplace_back(buf);

	std::getline(ss, buf);
	if(false ==__IsAllDigit(buf)) {
		sprintf(err_msg, "ERR: valid chars are 0-9, +, = Only. (Line%d@%s)", __LINE__, __FILE__);
		throw std::exception(err_msg);
	}
	ret.emplace_back(buf);
	return ret;
}

bool SumChecker::__IsAllDigit(const std::string & str) {
	if(str.empty()) return false;
	for(char c : str) {
		if(false == isdigit(c)) return false;
	}
	return true;
}
