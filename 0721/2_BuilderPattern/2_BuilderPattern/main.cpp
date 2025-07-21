#include <string>
#define interface struct

class Cut{
public:
	Cut () = default;

#if 0
	//아래와 같이 파라미터화된 생성자는 인자가 많아질수록 가독성이 떨어지고, 안정성, 확장성도 떨어진다.
	Cut(const std::string & stype_name, int front, int back, int side)
		:style_name(stype_name),front(front),back(back),side(side) { }
#else
	//그래서 아래와 같이 setter를 이용
	//하지만, 이 방식은 가독성이 너무 떨어진다.
	void setFront(int f) {
		front = f;
	}
	void setSide(int s) {
		side = s;
	}
	void setBack(int b) {
		back = b;
	}
#endif

private:
	std::string style_name;
	int front, side, back;
};

int main() {
	Cut cut;
	cut.setBack(3);
	cut.setSide(3);
	cut.setFront(2);
	return 0;
}