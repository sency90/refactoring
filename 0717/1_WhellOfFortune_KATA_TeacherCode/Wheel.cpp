#include <string>
#include <vector>

using std::string;
using std::vector;

class Wheel {
public:
	int getPrice(const vector<string> &strs, string userdata) {
		bool isFlip[4][15] = {false};

		int conCnt = 0;
		int ffirst[4] = {0};

		int sum = 0;
		int chance[4] = {-1, -1, -1, -1};

		//하나씩 처리
		//26글자 for 돌면서 퀴즈 참석자가 하나씩 시도를 하는 것
		for(int i = 0; i < 26; i++) {

			char userAnswer = userdata[i];

			//1. 2000 달러 찬스를 얻었는지 검사
			for(int y = 0; y < strs.size(); y++) {
				if(chance[y] != -1) {
					for(int x = 0; x < strs[chance[y]].size(); x++) {
						if(isFlip[chance[y]][x]) continue;
						if(strs[chance[y]][x] != userAnswer) continue;
						//획득 성공시 2000달러를 얻는다.
						sum += 2000;
						break;
					}
					chance[y] = -1;
				}
			}


			//Let's First 점수인지 확인한다.
			for(int y = 0; y < strs.size(); y++) {
				for(int x = 0; x < strs[y].size(); x++) {
					if(isFlip[y][x]) continue;
					if(strs[y][x] != userAnswer) continue;

					if(ffirst[y] == 0 && x == 0) {
						sum += 1000;
						ffirst[y] = 1;
						chance[y] = y;
					}
					else if(ffirst[y] == 0 && x != 0) {
						ffirst[y] = 1;
					}
				}
			}
			//동일한 문자 개수를 Counting한다.
			int passCnt = getPassCount(strs, isFlip, userAnswer);


			//뒤집었다면 체크해준다.
			updateFlipStatus(strs, isFlip, userAnswer);

			if(passCnt > 0) {
				conCnt++;
				sum += (conCnt * 100) * passCnt;
			}
			else {
				conCnt = 0;
				for(int i = 0; i < 4; i++) chance[i] = -1;
			}
		}

		return sum;
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