#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_device.cpp"

class FlashMock : public FlashMemoryDevice{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long addres, unsigned char data), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDevice* hardware = new FlashDevice();
	DeviceDriver driver{ hardware };
	int data = driver.read(0xFF);
	EXPECT_EQ(0, data);
}

TEST(DeviceDriver, Read5Times) {
	FlashMock mock;
	EXPECT_CALL(mock, read(0xBU)).Times(5);

	//DeviceDriver가 read()하면 FlashMemoryDevice를 5번 read()해야 한다.
	DeviceDriver driver{ &mock };
	int data = driver.read(0xBU);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
