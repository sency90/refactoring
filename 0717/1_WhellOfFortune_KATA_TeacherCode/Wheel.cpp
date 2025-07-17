#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Wheel {
public:
	int getPrice(const vector<string> &strs, string userdata) {
		bool isFlip[4][15] = {false};

		int continueTouchedCount = 0;
		bool isPossibleGetFirstChance[4] = {true, true, true, true};

		int sum = 0;
		int isOpenSecondChance[4] = {false};

		//하나씩 처리
		//26글자 for 돌면서 퀴즈 참석자가 하나씩 시도를 하는 것
		for(int i = 0; i < 26; i++) {

			char userAnswer = userdata[i];

			//동일한 문자 개수를 Counting한다.
			int passCnt = getPassCount(strs, isFlip, userAnswer);

			if(passCnt == 0) {
				continueTouchedCount = 0;
				for(int i = 0; i < 4; i++) isOpenSecondChance[i] = false;
				continue;
			}

			vector<int> firstLines = getFirstChanceLines(strs, isFlip, userAnswer, isPossibleGetFirstChance);
			int secondChanceCount = getSecondChanceCount(strs, isOpenSecondChance, isFlip, userAnswer);


			//상금얻자
			sum += (++continueTouchedCount * 100) * passCnt;
			sum += (1000 * firstLines.size());
			sum += (secondChanceCount * 2000);

			updateFirstChanceStatus(strs, isFlip, userAnswer, isPossibleGetFirstChance);
			updateSecondChanceStatus(firstLines, isOpenSecondChance);
			updateFlipStatus(strs, isFlip, userAnswer);
		}

		return sum;
	}
	void updateSecondChanceStatus(std::vector<int>& firstLines, int isOpenSecondChance[4]) {
		clearSecondChanceStatus(isOpenSecondChance);
		for(int line : firstLines) {
			isOpenSecondChance[line] = true;
		}
	}

	void updateFirstChanceStatus(const std::vector<std::string>& strs, bool  isFlip[4][15], char userAnswer, bool isPossibleGetFirstChance[4]) {
		for(int y = 0; y < strs.size(); y++) {
			for(int x = 0; x < strs[y].size(); x++) {
				if(isFlip[y][x]) continue;
				if(strs[y][x] != userAnswer) continue;
				isPossibleGetFirstChance[y] = false;
			}
		}
	}

	std::vector<int> getFirstChanceLines(const std::vector<std::string>& strs, bool  isFlip[4][15], char userAnswer, bool isPossibleGetFirstChance[4]) {
		std::vector<int> firstLines;
		for(int y = 0; y < strs.size(); y++) {
			for(int x = 0; x < strs[y].size(); x++) {
				if(isFlip[y][x]) continue;
				if(strs[y][x] != userAnswer) continue;
				if(isPossibleGetFirstChance[y] == false) continue;
				if(x != 0) continue;
				firstLines.push_back(y);
			}
		}
		return firstLines;
	}

	void clearSecondChanceStatus(int isOpenSecondChance[]) {
		std::fill(isOpenSecondChance, isOpenSecondChance + 4, false);
	}

	int getSecondChanceCount(const std::vector<std::string>& strs, int isOpenSecondChance[4], bool isFlip[4][15], char userAnswer) {
		int result = 0;
		for(int y = 0; y < strs.size(); y++) {
			if(isOpenSecondChance[y] == true) {
				for(int x = 0; x < strs[y].size(); x++) {
					if(isFlip[y][x]) continue;
					if(strs[y][x] != userAnswer) continue;
					result += 1;
					break;
				}
			}
		}
		return result;
	}
	void updateFlipStatus(const std::vector<std::string>& strs, bool isFlip[4][15], char userAnswer) {
		for(int y = 0; y < strs.size(); y++) {
			for(int x = 0; x < strs[y].size(); x++) {
				if(isFlip[y][x]) continue;
				if(strs[y][x] != userAnswer) continue;
				isFlip[y][x] = true;
			}
		}
	}

	int getPassCount(const std::vector<std::string>& strs, bool  isFlip[4][15], char userAnswer) {
		int result = 0;
		for(int y = 0; y < strs.size(); y++) {
			for(int x = 0; x < strs[y].size(); x++) {
				if(isFlip[y][x]) continue;
				if(strs[y][x] != userAnswer) continue;
				result++;
			}
		}
		return result;
	}
};