#define PRINT_DEBUG
#include "opcodes.hpp"
#include "utils.hpp"

constexpr word MEMORY_SIZE = 0xffff;
constexpr word ORIGIN = 0x3000;

byte memory[MEMORY_SIZE];
word pc = ORIGIN;

bool load_program(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == nullptr) {
        dbg("unable to open file %s", filename);
        return false;
    }

    word max_read = MEMORY_SIZE - ORIGIN;
    byte* program = memory + ORIGIN;

    word read = fread(program, sizeof(byte), max_read, file);
    dbg("loaded %zu bytes into memory at 0x%04x", read, ORIGIN);

    if (fclose(file) != 0) {
        dbg("unable to close file %s", filename);
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        err(1, "usage: %s <program>", argv[0]);
    }

    if (!load_program(argv[1])) {
        err(2, "failed to load program: %s", argv[1]);
    }

    bool running = true;
    while (running) {
        byte opcode = memory[pc++];

        switch (opcode) {
        case VNOP:
            dbg("NOP");
            break;
        case VHLT:
            running = false;
            dbg("HLT");
            break;
        default:
            err(3, "unknown opcode: 0x%02x", opcode);
            break;
        }
    }

    return 0;
}
