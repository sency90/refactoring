#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Wheel {
public:
	int getPrice(std::vector<std::string> strs, std::string userdata);
	int GetFirstChanceScore(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_1st_char, const std::vector<bool> & first_chance_by_lineno, bool *second_chance_by_lineno);
	void UpdateFirstAndSecondChance(std::vector<std::string>& quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char, std::vector<bool>& first_chance_by_lineno, bool *second_chance_by_lineno);
	void UpdateFlipStatus(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char);
	int GetPassCount(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char);
	int GetSecondChanceScore(std::vector<std::string> &strs, bool *chance_by_lineno, vector<vector<bool>>, char user_ans);
};

