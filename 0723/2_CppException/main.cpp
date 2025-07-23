#include <iostream>
#include <stdexcept>

int run(int n) {
	if(n==1) {
		throw std::exception("¾Æ ¾ÈµÅ~");
	}
}

int main() {
	try {
		std::cout << run(1);
	}
	catch(...) {
		std::cout << "...¿¡ µµÂø\n";
	}
	return 0;
}