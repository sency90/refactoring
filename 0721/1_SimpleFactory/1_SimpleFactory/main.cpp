#include <cstdio>
#include <string>

class Doll{
public:
	virtual void push() = 0;
};

class BlueDoll : public Doll{
public:
	void push() {
		printf("I'm a BLUE Doll");
	}
};

class RedDoll : public Doll{
public:
	void push() {
		printf("I'm a RED Doll");
	}
};

class Factory {
public:
	Doll* makeDoll(std::string name) {
		if(name == "RED") return new RedDoll();
		else if(name == "BLUE") return new BlueDoll();
		else return nullptr;
	}
	
};
int main() {
	Factory factory;
	Doll *doll = factory.makeDoll("RED");
	doll->push();
	return 0;
}