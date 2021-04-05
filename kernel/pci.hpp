#pragma once

#include <array>
#include <cstdint>

#include "error.hpp"

namespace pci {
// config_address register io port address
const uint16_t kConfigAddress = 0x0cf8;
// config_data register io port address
const uint16_t kConfigData = 0x0cfc;

struct ClassCode {
    uint8_t base, sub, interface;
    bool Match(uint8_t b) { return b == base; }
    bool Match(uint8_t b, uint8_t s) { return Match(b) && s == sub; }
    bool Match(uint8_t b, uint8_t s, uint8_t i) {
        return Match(b, s) && i == interface;
    }
};

struct Device {
    uint8_t bus, device, function, header_type;
    ClassCode class_code;
};
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
ClassCode ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);

inline uint16_t ReadVenderId(const Device &dev) {
    return ReadVenderId(dev.bus, dev.device, dev.function);
}

uint32_t ReadConfReg(const Device &dev, uint8_t reg_addr);

void WriteConfReg(const Device &dev, uint8_t reg_addr, uint32_t value);

// read bus numbers
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);
// Is single function device
bool IsSingleFunctionDevice(uint8_t header_type);

// pci device list
inline std::array<Device, 32> devices;
inline int num_device;

Error ScanAllBus();

constexpr uint8_t CalcBarAddress(unsigned int bar_index) {
    return 0x10 + 4 * bar_index;
}

WithError<uint64_t> ReadBar(Device &device, unsigned int bar_index);
} // namespace pci