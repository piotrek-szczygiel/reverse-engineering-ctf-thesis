#pragma once
#include "utils.hpp"

enum : byte {
    VNOP = 0xde,
    VHLT = 0x00,
    VSET = 0x17,
    VINP = 0xe9,
    VOUT = 0xb3,
    COUNT_OPCODES,
};

enum : byte {
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10,
    R11,
    R12,
    R13,
    SP,
    PC,
    COUNT_REGISTERS,
};
