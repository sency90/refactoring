#include <string>

using std::string;

class Greetable {
public:
	virtual string Greet() = 0;
};

class Formal : public Greetable {
public:
	string Greet() override {
		return "Good evening, sir.";
	}
};

class Casual : public Greetable {
public:
	string Greet() override {
		return "Sup bro?";
	}
};

class Intimate : public Greetable {
public:
	string Greet() override {
		return "Hello Darling!";
	}
};

class Normal : public Greetable {
public:
	string Greet() override {
		return "Hello.";
	}
};

class Greeter {
public:
	string Greet() {
		greet->Greet();
	}

	void SetFormality(Greetable *greet) {
		this->greet = greet;
	}

private:
	Greetable *greet;
};