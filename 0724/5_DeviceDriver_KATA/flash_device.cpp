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
		return 0xFF;
	}
	void write(long address, unsigned char data) override {
		memory[address] = data;
	}
private:
	map<ADDR, DATA> memory;
};