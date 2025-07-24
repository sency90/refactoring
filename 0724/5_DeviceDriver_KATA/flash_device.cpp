#include <map>
#include "flash_memory_device.h"

#define ADDR int
#define DATA int
using std::map;

class FlashDevice : public FlashMemoryDevice {
public:
	// FlashMemoryDevice��(��) ���� ��ӵ�
	unsigned char read(long address) override {
		return 0;
	}
	void write(long address, unsigned char data) override {
	}
private:
	map<ADDR, DATA> memory;
};