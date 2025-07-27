#pragma once
#include "flash_memory_device.h"
#include "read_fail_exception.h"
#include "write_fail_exception.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice *hardware);
    int read(long address) const;
    void write(long address, int data);

protected:
    FlashMemoryDevice *m_hardware;
};
