#include <iostream>
#include <stdexcept>

using std::cout;

class NotAllowedSix : public std::exception{
public:
	NotAllowedSix(const char * msg) : exception{msg} {}
};

int run(int n) {
	if(n==1) {
		throw NotAllowedSix("run(): NotAllowedSix Exception Occured!\n");
	}
}

int main() {
	try {
		cout << run(1);
	}
	catch(const NotAllowedSix & e) {
		cout << "try-catch(): NotAllowedSix Exception Occured!\n";
		cout << e.what() << "\n";
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