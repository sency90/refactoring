#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_device.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long addres, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDevice* hardware = new FlashDevice();
	DeviceDriver driver{ hardware };
	int data = driver.read(0xBU);
	EXPECT_EQ(0xFF, data);
}

TEST(DeviceDriver, Read5Times) {
	FlashMock mock;
	EXPECT_CALL(mock, read(0xBU)).Times(5);

	//DeviceDriver�� read()�ϸ� FlashMemoryDevice�� 5�� read()�ؾ� �Ѵ�.
	DeviceDriver driver{ &mock };
	int data = driver.read(0xBU);
}

TEST(DeviceDriver, ReadBeforeWrite) {
	//NiceMock�� stub�� ������ �����ϰ� ���ش�.
	//stub: �����ε� ������ �����ϴ� ��ó�� ���� ��.
	FlashMock mock;

	EXPECT_CALL(mock, read(0xBU))
		.Times(1).WillOnce(Return(0xFF));

	EXPECT_CALL(mock, write(0xBU,_))
		.Times(1);

	DeviceDriver driver{&mock};
	driver.write(0xBU, 7);
}

TEST(DeviceDriver, ReturnsSameValueAfterFiveReads) {
	FlashMock mock;

	long address = 0xBU;
	int writtenData = 10;
	int noData = 0xFF;

#if 1 //write
	EXPECT_CALL(mock, read(address))
		.Times(1).WillOnce(Return(noData));

	EXPECT_CALL(mock, write(address,writtenData))
		.Times(1);

	DeviceDriver driver{&mock};
	driver.write(address, writtenData);
#endif

#if 1 //read
	EXPECT_CALL(mock, read(address))
		.Times(5).WillRepeatedly(Return(writtenData));

	int outputData = driver.read(address);
	EXPECT_EQ(outputData, writtenData);
#endif
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
