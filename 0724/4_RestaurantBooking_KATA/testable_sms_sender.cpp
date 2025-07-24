#include <iostream>
#include "sms_sender.cpp"

using std::cout;

class TestableSmsSender : public SmsSender{
public:
	void send(Schedule* schedule) override {
		cout << "테스트용 SmsSender class의 send메서드 실행됨\n";
		sendMethodIsCalled = true;
	}
	bool isSendMethodIsCalled() const {
		return sendMethodIsCalled;
	}

private:
	 bool sendMethodIsCalled;
};