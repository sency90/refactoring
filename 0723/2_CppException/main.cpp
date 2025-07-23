#include <iostream>
#include <stdexcept>

using std::cout;

int run(int n) {
	if(n==1) {
		throw std::invalid_argument("아 안돼~");
	}
}

int main() {
	try {
		cout << run(1);
	}
	catch(const std::invalid_argument & e) {
		cout << "std::invalid_argument 예외 발생\n";
		cout << e.what() << "\n";
	}
	catch(const std::exception & e) {
		cout << "std::exception\n";
		cout << e.what() << "\n";
	}
	catch(...) {
		cout << "etc\n";
	}
	return 0;
}