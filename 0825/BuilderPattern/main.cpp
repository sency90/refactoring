#include <cstdio>
#include <string>
using namespace std;
class Cut {
public:
	Cut &setStyle(const std::string &style) {
		this->style = style;
		return *this;
	}

	Cut &setFront(int front) {
		this->front = front;
		return *this;
	}

	Cut &setBack(int back) {
		this->back = back;
		return *this;
	}

	Cut &setSide(int side) {
		this->side = side;
		return *this;
	}

	Cut &setGuretnaru(int guretnaru) {
		this->guretnaru = guretnaru;
		return *this;
	}

	Cut &setMustache(int mustache) {
		this->mustache = mustache;
		return *this;
	}

private:
	std::string style;
	int front, back, side, guretnaru, mustache;
};
int main() {
	//그래서 method chaining 방식을 이용
	//하지만, user(client)가 실수로 세팅 하나를 놓칠 수 있다.
	//또한, setting순서가 중요한 경우에도 이를 실수할 수 있다.
	Cut soldier_cut;
	soldier_cut.setStyle("Soldier").setFront(1).setBack(1).setSide(1);
	return 0;
}