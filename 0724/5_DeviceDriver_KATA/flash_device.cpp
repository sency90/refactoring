//**��... Story�� �� flash_device�� ��� �̿ϼ��� ���¿��� �ϴ±���**
#include "flash_memory_device.h"

class FlashDevice : public FlashMemoryDevice {
public:
	unsigned char read(long address) const override {
		return 0;
	}
	void write(long address, unsigned char data) override {
	}
};