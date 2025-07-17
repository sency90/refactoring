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

	int GetHp() const {
		return hp_;
	}

private:
	int hp_;
};

#if 1 //Composition
class DogHandler {
private:
	Dog dog; //Composition (has-a)

public:
	void PrintHP() {
		cout << "HP ���� ȭ�鿡 ����մϴ�\n";
		cout << "HP : " << dog.GetHp() << "\n";
	}

	void SendDB() {
		cout << "DB�� ������ ��� (hp: " << dog.GetHp() << ")\n";
	}
};
#endif

#if 1 //Association
class DogHandler{
private:
	Dog *dog; //Association (has-a)

public:
	DogHandler(Dog *dog):dog(dog) {}

	void PrintHP() {
		cout << "HP ���� ȭ�鿡 ����մϴ�\n";
		cout << "HP : " << dog->GetHp() << "\n";
	}

	void SendDB() {
		cout << "DB�� ������ ��� (hp: " << dog->GetHp() << ")\n";
	}
};
#endif

#if 1 //Dependency
class DogHandler {
public:
	void PrintHP(Dog * dog) {
		if(dog == nullptr) return;
		cout << "HP ���� ȭ�鿡 ����մϴ�\n";
		cout << "HP : " << dog->GetHp() << "\n";
	}

	void SendDB(Dog * dog) {
		cout << "DB�� ������ ��� (hp: " << dog->GetHp() << ")\n";
	}
};
#endif

int main() {
	return 0;
}
