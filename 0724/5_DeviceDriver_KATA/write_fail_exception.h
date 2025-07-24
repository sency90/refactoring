#pragma once
#include <stdexcept>
#include <string>
using std::string;
class WriteFailException: public std::exception {
public:
	WriteFailException():std::exception() {}
	WriteFailException(const std::string & msg):std::exception(msg.c_str()) {}
};
