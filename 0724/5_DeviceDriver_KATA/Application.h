#pragma once
#include "device_driver.h"
class Application {
public:
	Application(DeviceDriver *deviceDriver);

	void readAndPrint(int startAddr, int endAddr) const;
	void writeAll(int value);

private:
	DeviceDriver *deviceDriver = nullptr;
};

