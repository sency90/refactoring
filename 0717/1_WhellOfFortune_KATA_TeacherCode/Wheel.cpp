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

		//�ϳ��� ó��
		//26���� for ���鼭 ���� �����ڰ� �ϳ��� �õ��� �ϴ� ��
		for(int i = 0; i < 26; i++) {

			char userAnswer = userdata[i];

			//1. 2000 �޷� ������ ������� �˻�
			for(int y = 0; y < strs.size(); y++) {
				if(chance[y] != -1) {
					for(int x = 0; x < strs[chance[y]].size(); x++) {
						if(isFlip[chance[y]][x]) continue;
						if(strs[chance[y]][x] != userAnswer) continue;
						//ȹ�� ������ 2000�޷��� ��´�.
						sum += 2000;
						break;
					}
					chance[y] = -1;
				}
			}


			//Let's First �������� Ȯ���Ѵ�.
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
			//������ ���� ������ Counting�Ѵ�.
			int passCnt = getPassCount(strs, isFlip, userAnswer);


			//�������ٸ� üũ���ش�.
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