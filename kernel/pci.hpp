#pragma once

#include <array>
#include <cstdint>

#include "error.hpp"

namespace pci {
// config_address register io port address
const uint16_t kConfigAddress = 0x0cf8;
// config_data register io port address
const uint16_t kConfigData = 0x0cfc;

// write config_address register
void WriteAddress(uint32_t address);
// write config_data register
void WriteData(uint32_t value);
// read config_data register
uint32_t ReadData();

// read vender id register
uint16_t ReadVenderId(uint8_t bus, uint8_t device, uint8_t function);
// read device id register
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
// read header type register
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
// read class code register
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
// read bus numbers
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);
// Is single function device
bool IsSingleFunctionDevice(uint8_t header_type);

struct Device {
    uint8_t bus, device, function, header_type;
};

// pci device list
inline std::array<Device, 32> devices;
inline int num_device;

Error ScanAllBus();
} // namespace pci