#include <cstdio>
#include <string>
#include <stdexcept>
#include <cstdlib>
using namespace std;
class Cut {
public:
	class Builder {
	public:
		Builder &setStyle(const std::string &style) {
			this->style = style;
			return *this;
		}

		Builder &setFront(int front) {
			this->front = front;
			return *this;
		}

		Builder &setBack(int back) {
			this->back = back;
			return *this;
		}

		Builder &setSide(int side) {
			this->side = side;
			return *this;
		}

		Builder &setGuretnaru(int guretnaru) {
			this->guretnaru = guretnaru;
			return *this;
		}

		Builder &setMustache(int mustache) {
			this->mustache = mustache;
			return *this;
		}

		Cut build() {
			return Cut(style, front, back, side);
		}


	private:
		std::string style;
		int front, back, side, guretnaru, mustache;
	};

public:
	Cut()=default;
	void setCut(const Cut &cut) {
		*this = cut;
		validateArguments();
	}

private:
	Cut(const std::string &style, int front, int back, int side, int guretnaru=0, int mustache=0)
		: style(style), front(front), back(back), side(side), guretnaru(guretnaru), mustache(mustache) {
	}

	void validateArguments() const {
		if(!style.empty()) {
			throw std::invalid_argument("Style name must be set.");
		}
		if(front<=0) {
			throw std::invalid_argument("Front hair must be greater than 0cm.");
		}
		if(back<=0) {
			throw std::invalid_argument("...");
		}
		if(side<=0) {
			throw std::invalid_argument("...");
		}
	}

	std::string style;
	int front, back, side, guretnaru, mustache;
};
int main() {
	//그래서 method chaining 방식을 이용
	//하지만, user(client)가 실수로 세팅 하나를 놓칠 수 있다.
	//또한, setting순서가 중요한 경우에도 이를 실수할 수 있다.
	Cut soldier_cut;
	soldier_cut.setCut(Cut::Builder().setFront(1).setBack(1).setSide(1).build());
	return 0;
}