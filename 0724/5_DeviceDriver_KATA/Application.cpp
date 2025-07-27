#include "Application.h"

Application::Application(DeviceDriver *deviceDriver): deviceDriver(deviceDriver) {}

void Application::readAndPrint(int startAddr, int endAddr) const {
	for(int addr = startAddr; addr <= endAddr; addr++) {
		int data = deviceDriver->read(addr);
		printf("[0x%08X]: %d\n", addr, data);
	}
}

void Application::writeAll(int value) {
	for(int addr = 0x0; addr <= 0x4; addr++) {
		deviceDriver->write(addr, value);
	}
}
