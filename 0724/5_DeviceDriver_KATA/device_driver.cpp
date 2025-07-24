#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
	: m_hardware(hardware) {}

int DeviceDriver::read(long address) {
	// TODO: implement this method properly
	int readDataFirst = (int)(m_hardware->read(address));

	//read 4 times more
	for(int i=0; i<4; i++) {
		int readDataNow = (int)(m_hardware->read(address));
		if(readDataNow == readDataFirst) continue;

		throw ReadFailException();
	}

	const int & readDataFinal = readDataFirst;
	return readDataFinal;
}

void DeviceDriver::write(long address, int data) {
	// TODO: implement this method
	int readData = m_hardware->read(address);

	if(readData == 0xFF) {
		m_hardware->write(address, (unsigned char)data);
		return;
	}

	throw WriteFailException();
}
