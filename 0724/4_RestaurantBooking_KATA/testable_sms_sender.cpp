#include <iostream>
#include "sms_sender.cpp"

using std::cout;

class TestableSmsSender : public SmsSender{
public:
	void send(Schedule* schedule) override {
		cout << "�׽�Ʈ�� SmsSender class�� send�޼��� �����\n";
		sendMethodIsCalled = true;
	}
	bool isSendMethodIsCalled() const {
		return sendMethodIsCalled;
	}

private:
	 bool sendMethodIsCalled;
};