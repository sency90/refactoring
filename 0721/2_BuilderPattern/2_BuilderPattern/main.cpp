#include <string>
#include <cstdio>
#define interface struct
#define METHOD_CHAINING_METHOD

class Cut {
public:
	Cut(){}
#ifdef CONSTRUCTOR_METHOD
	//�Ʒ��� ���� �Ķ����ȭ�� �����ڴ� ���ڰ� ���������� �������� ��������, ������, Ȯ�强�� ��������.
	Cut(const std::string& stype_name, int front, int back, int side)
		:style_name(stype_name), front(front), back(back), side(side) {}
#elif defined SETTER_METHOD
	//�׷��� �Ʒ��� ���� setter�� �̿�
	//������, �� ����� �������� �ʹ� ��������.
	void setStyleName(const std::string& style_name) {
		this->style_name = style_name;
	}
	void setFront(int f) {
		front = f;
	}
	void setSide(int s) {
		side = s;
	}
	void setBack(int b) {
		back = b;
	}
#elif defined METHOD_CHAINING_METHOD
	Cut& setStyleName(const std::string & style_name) {
		this->style_name = style_name;
		return *this;
	}
	Cut& setFront(int f) {
		front = f;
		return *this;
	}
	Cut& setSide(int s) {
		side = s;
		return *this;
	}
	Cut& setBack(int b) {
		back = b;
		return *this;
	}
#endif

	void print() const {
		printf("style_name: %s\n", style_name.c_str());
		printf("front: %d, back:%d, side:%d\n", front, back, side);
	}

private:
	std::string style_name;
	int front, side, back;
};

int main() {
#ifdef CONSTRUCTOR_METHOD
	Cut cut("good-style", 3,3,2);
#elif defined SETTER_METHOD
	Cut cut;
	cut.setStyleName("good-style");
	cut.setBack(3);
	cut.setSide(3);
	cut.setFront(2);
#elif defined METHOD_CHAINING_METHOD
	Cut & cut = (*(new Cut())).setStyleName("good-style").setFront(2).setBack(3).setSide(3);
	cut.print();
#endif
	return 0;
}