#include "sms_sender.cpp"
#include "gmock/gmock.h"

class TestableSmsSender: public SmsSender {
public:
	MOCK_METHOD(void, send, (Schedule*), (override));
};