#pragma once
#include <stdexcept>
#include <string>
using std::string;
class ReadFailException: public std::exception {
public:
	ReadFailException():std::exception() {}
	ReadFailException(const std::string & msg):std::exception(msg.c_str()) {}
};
