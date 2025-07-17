#include <iostream>

using std::cout;

class Dog {
public:
	void Walk() {
		cout << "걷다\n";
	}

	void Bark() {
		cout << "왕왕\n";
	}

	void printHP() {
		cout << "HP 값을 화면에 출력합니다\n";
		cout << "HP : " << hp_ << "\n";
	}

	void SendDB() {
		cout << "DB에 데이터 기록\n";
	}

private:
	int hp_;
};
