#include <iostream>
#include <stdexcept>

int run(int n) {
	if(n==1) {
		throw std::exception("�� �ȵ�~");
	}
}

int main() {
	try {
		std::cout << run(1);
	}
	catch(...) {
		std::cout << "...�� ����\n";
	}
	return 0;
}