#include <string>
#define interface struct

class Cut{
public:
	Cut () = default;

#if 0
	//�Ʒ��� ���� �Ķ����ȭ�� �����ڴ� ���ڰ� ���������� �������� ��������, ������, Ȯ�强�� ��������.
	Cut(const std::string & stype_name, int front, int back, int side)
		:style_name(stype_name),front(front),back(back),side(side) { }
#else
	//�׷��� �Ʒ��� ���� setter�� �̿�
	//������, �� ����� �������� �ʹ� ��������.
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