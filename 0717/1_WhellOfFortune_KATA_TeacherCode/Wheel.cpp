#include <string>
#include <vector>
#include <iostream>
#include <set>

using std::string;
using std::vector;

struct Point {
	int x, y;
};

class Wheel {
public:
	int getPrice(const vector<string> &strs, const string &userdata) {
		int totalPrice = 0;

		for(int i = 0; i < MAX_TRY_ANSWER_COUNT; i++) {
			char userAnswer = userdata[i];

			vector<Point> answerPoints = getAnswerPoints(strs, userAnswer);

			int passCnt = answerPoints.size();
			if(passCnt == 0) {
				continueTouchedCount = 0;
				clearSecondChanceStatus();
				continue;
			}

			continueTouchedCount += 1;

			//First, Second 찬스 확인하기
			vector<int> firstLines = getFirstChanceLines(answerPoints);
			int secondChanceCount = getSecondChanceCount(answerPoints);

			//상금 
			totalPrice += (100 * continueTouchedCount) * passCnt;
			totalPrice += (1000 * firstLines.size());
			totalPrice += (2000 * secondChanceCount);

			//게임 상태 업데이트
			updateFirstChanceStatus(answerPoints);
			updateSecondChanceStatus(firstLines);
			updateFlipStatus(answerPoints);
		}

		return totalPrice;
	}

private:
	vector<Point> getAnswerPoints(const std::vector<std::string>& strs, char userAnswer) const {
		vector<Point> points;
		int result = 0;
		for(int y = 0; y < strs.size(); y++) {
			for(int x = 0; x < strs[y].size(); x++) {
				if(isFlip[y][x]) continue;
				if(strs[y][x] != userAnswer) continue;
				points.push_back({x, y});
			}
		}
		return points;
	}

	std::vector<int> getFirstChanceLines(const vector<Point>& answerPoints) const {
		std::vector<int> firstLines;
		for(Point point : answerPoints) {
			if(point.x != 0) continue;
			if(isPossibleGetFirstChance[point.y] == false) continue;
			firstLines.push_back(point.y);
		}
		return firstLines;
	}

	int getSecondChanceCount(vector<Point> answerPoints) const {
		std::set<int> DistintLines;

		for(Point point : answerPoints) {
			if(isOpenSecondChance[point.y] == false) continue;
			DistintLines.insert(point.y);
		}

		return DistintLines.size();
	}

	void updateFirstChanceStatus(const vector<Point>& answerPoints) {
		for(Point point : answerPoints) {
			isPossibleGetFirstChance[point.y] = false;
		}
	}

	void updateSecondChanceStatus(const std::vector<int>& firstLines) {
		clearSecondChanceStatus();
		for(int line : firstLines) {
			isOpenSecondChance[line] = true;
		}
	}

	void clearSecondChanceStatus() {
		std::fill(isOpenSecondChance, isOpenSecondChance + ANSWER_LINE_COUNT, false);
	}

	void updateFlipStatus(const vector<Point>& answerPoints) {
		for(Point point : answerPoints) {
			isFlip[point.y][point.x] = true;
		}
	}

	static const int MAX_TRY_ANSWER_COUNT = 26;
	static const int ANSWER_LINE_COUNT = 4;
	static const int ANSWER_LENGTH_COUNT = 15;

	bool isFlip[ANSWER_LINE_COUNT][ANSWER_LENGTH_COUNT] = {false};
	bool isPossibleGetFirstChance[ANSWER_LINE_COUNT] = {true, true, true, true};
	int isOpenSecondChance[ANSWER_LINE_COUNT] = {false};
	int continueTouchedCount = 0;
};