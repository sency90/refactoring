//**아... Story상 이 flash_device는 계속 미완성인 상태여야 하는구나**
#include "flash_memory_device.h"

class FlashDevice : public FlashMemoryDevice {
public:
	unsigned char read(long address) const override {
		return 0;
	}
	void write(long address, unsigned char data) override {
	}
};