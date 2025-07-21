#include <iostream>
#include <string>
#define interface struct

interface Jewelry{
	virtual void showInfo() = 0;
};

class Gold: public Jewelry {
public:
	Gold(int g, int s, int n):
		����{g}, ����{s}, ����{n} {}

	void showInfo() override {
		std::cout << "===���===\n";
		std::cout << "���� : " << ���� << '\n';
		std::cout << "���� : " << ���� << '\n';
		std::cout << "���� : " << ���� << '\n';
	}

private:
	int ���� = 0;
	int ���� = 0;
	int ���� = 0;
};

interface JewelryFactory{
	virtual Jewelry * make() = 0;
};

class GoldFactory: public JewelryFactory {
public:
	static GoldFactory& getInstance() {
		static GoldFactory instance;
		return instance;
	}

	Jewelry* make() {
		return new Gold(g, s, h);
	}

	GoldFactory& setGaro(int g) {
		this->g = g;
		return *this;
	}

	GoldFactory& setSero(int s) {
		this->s = s;
		return *this;
	}

	GoldFactory& setHeight(int h) {
		this->h = h;
		return *this;
	}

private:
	GoldFactory() = default;
	int g;
	int s;
	int h;
};

int main() {

	//Facotry, Singleton, �޼���ü�̴�
	GoldFactory factory = GoldFactory::getInstance();
	Jewelry* gold = factory.setGaro(10).setHeight(5).setSero(2).make();

	gold->showInfo();
}