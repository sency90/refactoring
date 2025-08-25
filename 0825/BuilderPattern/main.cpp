#include <cstdio>
#include <string>
using namespace std;
class Cut {
public:
	Cut(std::string style, int front, int back, int side, int guretnaru=0, int mustache=0)
		: style(style), front(front), back(back), side(side), guretnaru(guretnaru), mustache(mustache) {
	}

private:
	std::string style;
	int front, back, side, guretnaru, mustache;
};
int main() {
	// 아래와 같은 파라미터화된 생성자는 인자가 많아질수록 가독성이 떨어지고,
	// 안정성, 확장성이 떨어진다.
	// 각 Argument가 무슨 뜻인지 이 코드만으로는 알 수 없고, 
	// Argument를 실 수할 수 있음.
	Cut soldier_cur("Soldier", 1, 1, 1);
	return 0;
}