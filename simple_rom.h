#ifndef SIMPLE_ROM_H
#define SIMPLE_ROM_H

#include "hw/sysbus.h"
#include "qom/object.h"

DeviceState *simple_rom_create(hwaddr addr);

#endif
