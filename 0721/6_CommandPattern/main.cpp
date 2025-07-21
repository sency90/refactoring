#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class TV {
public:
	void chUp() {
		std::cout << "채널 업\n";
	}

	void chDown() {
		std::cout << "채널 다운\n";
	}
};

class Command { //interface
public:
	virtual void run() = 0;
	virtual void undo() = 0;
};

class UP: public Command {
public:
	UP(TV* tv): tv{tv} {}
	void run() override {
		tv->chUp();
	}

	void undo() override {
		tv->chDown();
	}
private:
	TV* tv;
};

class Down: public Command {
public:
	Down(TV* tv): tv{tv} {}
	void run() override {
		tv->chDown();
	}

	void undo() override {
		tv->chUp();
	}
private:
	TV* tv;
};

class RemoteControl {
public:
	void push(Command* cmd) {
		history.push_back(cmd);
		cmd->run();
	}

	void ctrlz() {
		history.back()->undo();
		history.pop_back();
	}

private:
	vector<Command*> history;
};

int main() {
	TV tv;
	RemoteControl rc;


	rc.push(new UP(&tv));
	rc.push(new Down(&tv));
	rc.push(new UP(&tv));
	rc.push(new UP(&tv));
	rc.push(new Down(&tv));

	rc.ctrlz();
	rc.ctrlz();
	rc.ctrlz();
	rc.ctrlz();
	rc.ctrlz();
}