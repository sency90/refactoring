#include <map>
#include "flash_memory_device.h"

#define ADDR int
#define DATA int
using std::map;

class FlashDevice : public FlashMemoryDevice {
public:
	// FlashMemoryDevice을(를) 통해 상속됨
	unsigned char read(long address) override {
		if(memory.count(address)>0) {
			return memory.at(address);
		}
		return 0;
	}
	void write(long address, unsigned char data) override {
	}
private:
	map<ADDR, DATA> memory;
};