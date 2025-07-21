#include <iostream>
#include <string>
#define interface struct

interface Jewelry{
	virtual void showInfo() = 0;
};

class Gold: public Jewelry {
public:
	Gold(int g, int s, int n):
		가로{g}, 세로{s}, 높이{n} {}

	void showInfo() override {
		std::cout << "===골드===\n";
		std::cout << "가로 : " << 가로 << '\n';
		std::cout << "세로 : " << 세로 << '\n';
		std::cout << "높이 : " << 높이 << '\n';
	}

private:
	int 가로 = 0;
	int 세로 = 0;
	int 높이 = 0;
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

	//Facotry, Singleton, 메서드체이닝
	GoldFactory factory = GoldFactory::getInstance();
	Jewelry* gold = factory.setGaro(10).setHeight(5).setSero(2).make();

	gold->showInfo();
}