#include "gmock/gmock.h"
#include "device_driver.h"
#include "flash_device.cpp"
#include "Application.h"

using namespace testing;

class FlashMemoryDeviceMock: public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (const override));
	MOCK_METHOD(void, write, (long addres, unsigned char data), (override));
};

class DeviceDriverFixture: public Test {
protected:
	virtual void SetUp() override {
		deviceDriver = new DeviceDriver{ &flashMemoryDeviceMock };
		app = new Application(deviceDriver);
	}

public:
	void expectWriteAfterEmptyCheck(int addr, int data) {
		EXPECT_CALL(flashMemoryDeviceMock, read(addr))
			.Times(1).WillOnce(Return(NO_DATA));

		EXPECT_CALL(flashMemoryDeviceMock, write(addr, data))
			.Times(1);

		deviceDriver->write(addr, data);
	}

public:
	FlashMemoryDeviceMock flashMemoryDeviceMock;
	DeviceDriver *deviceDriver = nullptr;
	Application *app = nullptr;

	const long MEMORY_ADDRESS = 0xBU;
	const int NO_DATA = 0xFF;
	const int INPUT_DATA = 'a';
	const int ANY_DATA_EXCEPT_NO_DATA = ~NO_DATA;
	const int K_FLASH_READS_PER_DEVICE_READ = 5;
	const int WRITE_ALL_START_ADDR = 0x0;
	const int WRITE_ALL_END_ADDR = 0x4;
};

TEST_F(DeviceDriverFixture, Read5Times) {
	EXPECT_CALL(flashMemoryDeviceMock, read(MEMORY_ADDRESS))
		.Times(5);

	//DeviceDriver가 read()하면 FlashMemoryDevice를 5번 read()해야 한다.
	int data = deviceDriver->read(MEMORY_ADDRESS);
}

TEST_F(DeviceDriverFixture, ReadBeforeWrite) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);
}

TEST_F(DeviceDriverFixture, ReturnsSameValueAfterFiveReads) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(flashMemoryDeviceMock, read(MEMORY_ADDRESS))
		.Times(5).WillRepeatedly(Return(INPUT_DATA));

	int outputData = deviceDriver->read(MEMORY_ADDRESS);
	EXPECT_EQ(outputData, INPUT_DATA);
#endif
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenFirstTwoReadsDiffer) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(flashMemoryDeviceMock, read(MEMORY_ADDRESS))
		.WillOnce(Return(INPUT_DATA-1))
		.WillOnce(Return(INPUT_DATA));

	EXPECT_THROW({ deviceDriver->read(MEMORY_ADDRESS); }, ReadFailException);
#endif

}
TEST_F(DeviceDriverFixture, ThrowsExceptionWhenLastReadDiffers) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

#if 1 //read
	EXPECT_CALL(flashMemoryDeviceMock, read(MEMORY_ADDRESS))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA-1));

	EXPECT_THROW({ deviceDriver->read(MEMORY_ADDRESS); }, ReadFailException);
#endif
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenWrite) {
	expectWriteAfterEmptyCheck(MEMORY_ADDRESS, INPUT_DATA);

	EXPECT_CALL(flashMemoryDeviceMock, read(MEMORY_ADDRESS))
		.WillOnce(Return(ANY_DATA_EXCEPT_NO_DATA));

	EXPECT_THROW({ deviceDriver->write(MEMORY_ADDRESS, INPUT_DATA); }, WriteFailException);
}

TEST_F(DeviceDriverFixture, AppTestForReadAndPrintFunction) {
	const int startAddr = 0x10;
	const int endAddr = 0x1F;
	const int deviceDriverReadCount = endAddr - startAddr + 1;
	const int totalFlashReadCount = deviceDriverReadCount * K_FLASH_READS_PER_DEVICE_READ;

	EXPECT_CALL(flashMemoryDeviceMock, read)
		.Times(totalFlashReadCount)
		.WillRepeatedly(Return(NO_DATA));

	app->readAndPrint(startAddr, endAddr);
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenReadAndPrint) {
	const int startAddr = 0x10;
	const int midAddr = 0x12;
	const int endAddr = 0x1F;
	const int aFewMoreFlashReadCount = K_FLASH_READS_PER_DEVICE_READ/2;

	const int deviceDriverReadCount = midAddr - startAddr + 1;
	const int totalFlashReadCount = deviceDriverReadCount * K_FLASH_READS_PER_DEVICE_READ + aFewMoreFlashReadCount;

	const int ANY_DATA_EXCEPT_INPUT_DATA = ~INPUT_DATA;
	EXPECT_CALL(flashMemoryDeviceMock, read)
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))

		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))

		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(INPUT_DATA))
		.WillOnce(Return(ANY_DATA_EXCEPT_INPUT_DATA));

	EXPECT_THROW({ app->readAndPrint(startAddr, endAddr); }, ReadFailException);
}

TEST_F(DeviceDriverFixture, AppTestForWriteAllFunction) {
	const int totalFlashReadCount = WRITE_ALL_END_ADDR - WRITE_ALL_START_ADDR +1;
	const int totalFlashWriteCount = totalFlashReadCount;

	EXPECT_CALL(flashMemoryDeviceMock, read)
		.Times(totalFlashReadCount)
		.WillRepeatedly(Return(NO_DATA));

	EXPECT_CALL(flashMemoryDeviceMock, write)
		.Times(totalFlashWriteCount);

	app->writeAll(INPUT_DATA);
}

TEST_F(DeviceDriverFixture, ThrowsExceptionWhenWriteAll) {
	const int totalFlashReadCount = WRITE_ALL_END_ADDR - WRITE_ALL_START_ADDR +1;

	EXPECT_CALL(flashMemoryDeviceMock, read)
		//.Times(totalFlashReadCount)
		//.WillRepeatedly(Return(ANY_DATA_EXCEPT_NO_DATA));
		.WillOnce(Return(ANY_DATA_EXCEPT_NO_DATA));

	EXPECT_THROW({ app->writeAll(INPUT_DATA); }, WriteFailException);
}


int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
