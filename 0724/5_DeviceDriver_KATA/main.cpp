#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_device.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long addres, unsigned char data), (override));
};

class DeviceDriverFixture: public Test{
protected:
	virtual void SetUp() override {
		driver = new DeviceDriver{&mock};
	}

public:
	void expectWriteAfterEmptyCheck(int addr, int data) {
		EXPECT_CALL(mock, read(addr))
			.Times(1).WillOnce(Return(NO_DATA));

		EXPECT_CALL(mock, write(addr, data))
			.Times(1);

		driver->write(addr, data);
	}

public:
	FlashMock mock;
	DeviceDriver *driver;

	const long MEMORY_ADDRESS = 0xBU;
	const int NO_DATA = 0xFF;
	const int INPUT_DATA = 10;
	const int ANY_DATA_EXCEPT_NO_DATA = ~NO_DATA;

};

TEST_F(DeviceDriverFixture, Read5Times) {
	EXPECT_CALL(mock, read(MEMORY_ADDRESS))
		.Times(5);

	//DeviceDriver가 read()하면 FlashMemoryDevice를 5번 read()해야 한다.
	int data = driver->read(MEMORY_ADDRESS);
}

TEST_F(DeviceDriverFixture, ReadBeforeWrite) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);
}

TEST_F(DeviceDriverFixture, ReturnsSameValueAfterFiveReads) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(mock, read(MEMORY_ADDRESS))
		.Times(5).WillRepeatedly(Return(INPUT_DATA));

	int outputData = driver->read(MEMORY_ADDRESS);
	EXPECT_EQ(outputData, INPUT_DATA);
#endif
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenFirstTwoReadsDiffer) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(mock, read(MEMORY_ADDRESS))
		.WillOnce(Return(INPUT_DATA-1))
		.WillOnce(Return(INPUT_DATA));

	EXPECT_THROW({driver->read(MEMORY_ADDRESS);}, ReadFailException);
#endif

}
TEST_F(DeviceDriverFixture, ThrowsExceptionWhenLastReadDiffers) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(mock, read(MEMORY_ADDRESS))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA-1));

	EXPECT_THROW({driver->read(MEMORY_ADDRESS);}, ReadFailException);
#endif
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenWrite) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

	EXPECT_CALL(mock, read(MEMORY_ADDRESS))
		.WillOnce(Return(ANY_DATA_EXCEPT_NO_DATA));

	EXPECT_THROW({driver->write(MEMORY_ADDRESS, INPUT_DATA);}, WriteFailException);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
