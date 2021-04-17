#pragma once

enum class DescriptorType {
    // system segment and gate descriptor types
    kUpper8Bits = 0,
    kLDT = 2,
    kTSSAvailable = 9,
    kTSSbusy = 11,
    kCallGate = 12,
    kInterruptGate = 14,
    kTrapGate = 15,

    // code and data segment types
    kReadWrite = 2,
    kExecuteRead = 10,
};