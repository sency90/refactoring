#include "Wheel.h"
#include <cstring>
using std::string;
using std::vector;

namespace{
	constexpr int NOTYET = -1;
	constexpr int DOLLAR_2000 = 2000;
};

int Wheel::getPrice(std::vector<std::string> quiz_lines,std::string user_ans) {
	static std::vector<std::vector<bool>> is_flipped;
	is_flipped.clear();
	is_flipped.resize(quiz_lines.size(), std::vector<bool>());
	for(int i=0; i<quiz_lines.size(); i++) {
		is_flipped[i].resize(quiz_lines[i].size(), false);
	}

	int conCnt = 0;
	static std::vector<bool> first_chance_by_lineno;
	first_chance_by_lineno.clear();
	first_chance_by_lineno.resize(4, true);

	int prize = 0;
	bool second_chance_by_lineno[4];
	memset(second_chance_by_lineno, false, sizeof(second_chance_by_lineno));

	vector<int> second_chance_lines;

	//하나씩 처리
	//26글자 for 돌면서 퀴즈 참석자가 하나씩 시도를 하는 것
	for(int z=0; z<user_ans.size(); z++) {
		char user_ans_char = user_ans[z];

		//1. 2000 달러 찬스를 얻었는지 검사
		prize += GetSecondChanceScore(quiz_lines, second_chance_by_lineno, is_flipped, user_ans_char);


#if 0
		int passCnt=0;
		//2중 for 돌면서 정답 문자열을 하나씩 검사해서
		//퀴즈참가자가 던진 문자가 존재하는지 검사
		for(int lineno = 0; lineno < quiz_lines.size(); lineno++) {
			std::string & quiz_line = quiz_lines[lineno];
			for(int i = 0; i < quiz_line.size(); i++) {
				if(is_flipped[lineno][i]) continue;

				//만약 퀴즈참석자가 요청한 문자가, 
				//정답문자열과 동일하다면
				if(quiz_line[i] == user_ans_char) {

					//Let's First 점수인지 확인한다.
					if(ffirst[lineno] == 0 && i == 0) {
						prize += 1000;
						ffirst[lineno] = 1;
						chance_by_lineno[lineno] = true;
					}
					else if(ffirst[lineno] == 0 && i != 0) {
						ffirst[lineno] = 1;
					}

					//used배열
					is_flipped[lineno][i] = true;

					//동일한 문자 개수를 Counting한다.
					passCnt++;
				}
			}
		}
#else

#if 0
		for(int lineno = 0; lineno < quiz_lines.size(); lineno++) {
			std::string & quiz_line = quiz_lines[lineno];
			for(int i = 0; i < quiz_line.size(); i++) {
				if(is_flipped[lineno][i]) continue;
				if(quiz_line[i] == user_ans_char) {
					//Let's First 점수인지 확인한다.
					if(first_chance_by_lineno[lineno] && i == 0) {
						prize += 1000;
						first_chance_by_lineno[lineno] = false;
						second_chance_by_lineno[lineno] = true;
					}
					else if(first_chance_by_lineno[lineno] && i != 0) {
						first_chance_by_lineno[lineno] = false;
					}
				}
			}
		}
#else
		prize += GetFirstChanceScore(quiz_lines, is_flipped, user_ans_char, first_chance_by_lineno, second_chance_by_lineno);
		UpdateFirstAndSecondChance(quiz_lines, is_flipped, user_ans_char, first_chance_by_lineno, second_chance_by_lineno);
#endif

		int passCnt = GetPassCount(quiz_lines, is_flipped, user_ans_char);
		UpdateFlipStatus(quiz_lines, is_flipped, user_ans_char);
#endif

		if(passCnt>0) {
			conCnt++;
			prize += (conCnt * 100) * passCnt;
		}
		else {
			conCnt = 0;
			memset(second_chance_by_lineno, false, sizeof(second_chance_by_lineno));
		}
	}

	return prize;
}

int Wheel::GetFirstChanceScore(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char, const std::vector<bool> & first_chance_by_lineno, bool *second_chance_by_lineno) {
	int result = 0;
	for(int lineno = 0; lineno < is_flipped.size(); lineno++) {
		if(quiz_lines[lineno][0] != user_ans_char) continue;
		if(is_flipped[lineno][0]) continue;
		if(false == first_chance_by_lineno[lineno]) continue;

		result += 1000;
	}
	return result;
}

void Wheel::UpdateFirstAndSecondChance(std::vector<std::string>& quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char, std::vector<bool>& first_chance_by_lineno, bool *second_chance_by_lineno) {
	for(int lineno = 0; lineno < quiz_lines.size(); lineno++) {
		std::string & quiz_line = quiz_lines[lineno];
		for(int i=0; i<quiz_line.size(); i++) {
			if(is_flipped[lineno][i]) continue;
			if(quiz_line[i] != user_ans_char) continue;

			if(i==0) {
				if(first_chance_by_lineno[lineno]) {
					first_chance_by_lineno[lineno] = false;
					second_chance_by_lineno[lineno] = true;
					break;
				}
			}

			first_chance_by_lineno[lineno] = false;
		}
	}
}

void Wheel::UpdateFlipStatus(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char) {
	for(int lineno = 0; lineno < quiz_lines.size(); lineno++) {
		std::string & quiz_line = quiz_lines[lineno];
		for(int i = 0; i < quiz_line.size(); i++) {
			if(is_flipped[lineno][i]) continue;
			if(quiz_line[i] == user_ans_char) {
				is_flipped[lineno][i] = true;
			}
		}
	}
}

int Wheel::GetPassCount(std::vector<std::string> &quiz_lines, std::vector<std::vector<bool>> &is_flipped, char user_ans_char)
{
	int result = 0;
	for(int lineno = 0; lineno < quiz_lines.size(); lineno++) {
		std::string & quiz_line = quiz_lines[lineno];
		for(int i = 0; i < quiz_line.size(); i++) {
			if(is_flipped[lineno][i]) continue;
			if(quiz_line[i] == user_ans_char) {
				result++; //동일한 문자 개수를 Counting한다.
			}
		}
	}
	return result;
}

int Wheel::GetSecondChanceScore(std::vector<std::string> &strs, bool *chance_by_lineno, vector<vector<bool>> is_flipped, char user_ans_char) {
	int ret=0;
	for(int lineno=0; lineno < strs.size(); lineno++) {
		if(false == chance_by_lineno[lineno]) continue;

		for(int i=0; i<strs[lineno].size(); i++) {
			if(is_flipped[lineno][i] == 0 && strs[lineno][i] == user_ans_char) {
				ret += DOLLAR_2000;
				break;
			}
		}
		chance_by_lineno[lineno] = false;
	}
	return ret;
}

