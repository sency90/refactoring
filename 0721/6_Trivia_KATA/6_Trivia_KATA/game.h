#pragma once
#define interface struct
#include <iostream>
#include <list>
#include <vector>
#include <string>

using std::string;
using std::list;
using std::vector;
using std::to_string;
using std::cout;
using std::endl;

interface IGame {
	virtual bool add(string player) = 0;
	virtual void rolling() = 0;
	virtual bool wasCorrectlyAnswered() = 0;
	virtual bool wrongAnswer() = 0;
};
