#include "qemu/osdep.h"
#include "hw/misc/simple_rom.h"
#include "qapi/error.h"
#include "hw/sysbus.h"

#define TYPE_SIMPLE_ROM "simple_rom"

/* Register map */
#define REG_ID  0x0
#define CHIP_ID 0xA0000001

/*
 * Structure to capture the state of simple rom
 */
typedef struct{
    SysBusDevice parent_obj;
    MemoryRegion iomem;
    uint64_t chip_id;
}SimpleRomState;

DECLARE_INSTANCE_CHECKER(SimpleRomState, SIMPLE_ROM, TYPE_SIMPLE_ROM)

static uint64_t simple_rom_read(void *opaque, hwaddr addr, unsigned int size)
{
    SimpleRomState *s = opaque;

    /* Return the chip id based on the address passed */
    switch (addr) {
        case REG_ID:
            return s->chip_id;
             break;

        default:
            return 0xDEEDDEED;
            break;
    }  

    return 0;
}

static const MemoryRegionOps simple_rom_ops = {
    .read = simple_rom_read,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void simple_rom_instance_init(Object *obj)
{
    /* Get the object state handle */
    SimpleRomState *s = SIMPLE_ROM(obj);

    /* Memory map region allocation */
    memory_region_init_io(&s->iomem, obj, &simple_rom_ops, s, TYPE_SIMPLE_ROM, 0x200);

    /* Initialize mmio sysbus */
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->iomem);

    /* Update chid id */
    s->chip_id = CHIP_ID;
}

/* create a new type to define the info related to our device */
static const TypeInfo simple_rom_info = {
    .name = TYPE_SIMPLE_ROM,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(SimpleRomState),
    .instance_init = simple_rom_instance_init,
};

static void simple_rom_register_types(void)
{
    type_register_static(&simple_rom_info);
}

type_init(simple_rom_register_types)

/*
 * Create the Simple Rom device.
 */
DeviceState *simple_rom_create(hwaddr addr)
{
    DeviceState *dev = qdev_new(TYPE_SIMPLE_ROM);
    sysbus_realize_and_unref(SYS_BUS_DEVICE(dev), &error_fatal);
    sysbus_mmio_map(SYS_BUS_DEVICE(dev), 0, addr);
    return dev;
}
