# simplerom
This is just a practice exercise to add simple rom device to QEMU.
All the devices in QEMU are represented as an object using QEMU object model which provides
infrastructure for registering and instantiating objects from the user defined types.
In this case the simple rom device inherits from the parent object which is the system bus.
Usually for the device emulation there will be more registers and irqs defined but in this case we define only chip ID register.
The device is mapped over the system bus and is memory mapped. 

