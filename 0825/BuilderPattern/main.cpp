#include <cstdio>
#include <string>
using namespace std;
class Cut {
public:
	void setStyle(const std::string &style) {
		this->style = style;
	}

	void setFront(int front) {
		this->front = front;
	}

	void setBack(int back) {
		this->back = back;
	}

	void setSide(int side) {
		this->side = side;
	}

	void setGuretnaru(int guretnaru) {
		this->guretnaru = guretnaru;
	}

	void setMustache(int mustache) {
		this->mustache = mustache;
	}

private:
	std::string style;
	int front, back, side, guretnaru, mustache;
};
int main() {
	//그래서 setter를 이용하게 되면, 더럽다.
	//가독성도 떨어지고, 전체적인 setting을 여러번 나눠서 해야하기 떄문에
	//코드가 여기저기 흩어질 수도 있고
	//setting 순서가 중요한 경우에도 이를 실수할 수 있다.
	Cut soldier_cut;
	soldier_cut.setStyle("Soldier");
	soldier_cut.setFront(1);
	soldier_cut.setBack(1);
	soldier_cut.setSide(1);
	return 0;
}