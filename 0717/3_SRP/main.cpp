#include <iostream>

using std::cout;

class Dog {
public:
	void Walk() {
		cout << "�ȴ�\n";
	}

	void Bark() {
		cout << "�տ�\n";
	}

	void printHP() {
		cout << "HP ���� ȭ�鿡 ����մϴ�\n";
		cout << "HP : " << hp_ << "\n";
	}

	void SendDB() {
		cout << "DB�� ������ ���\n";
	}

private:
	int hp_;
};
