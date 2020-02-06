#define PRINT_DEBUG
#include "vm.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

constexpr word MEMORY_SIZE = 0xffff;
constexpr word ORIGIN = 0x3000;

byte memory[MEMORY_SIZE];
word reg[COUNT_REGISTERS];

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

byte fetch_byte(word address) { return memory[address]; }
word fetch_word(word address) { return memory[address] | memory[address + 1] << 8; }

int main(int argc, char* argv[])
{
    if (argc != 2) {
        err(1, "usage: %s <program>", argv[0]);
    }

    if (!load_program(argv[1])) {
        err(2, "failed to load program: %s", argv[1]);
    }

    reg[PC] = ORIGIN;

    bool running = true;
    while (running) {
        byte opcode = memory[reg[PC]++];
        // dbg("opcode: 0x%02x", opcode);

        switch (opcode) {
        case VNOP: {
            dbg("VNOP");
            break;
        }
        case VHLT: {
            running = false;
            dbg("VHLT");
            break;
        }
        case VSET: {
            byte r = fetch_byte(reg[PC]++);
            reg[r] = fetch_word(reg[PC]);
            reg[PC] += 2;
            dbg("VSET\tR%u, 0x%04x", r, reg[r]);
            break;
        }
        case VINP: {
            byte r = fetch_byte(reg[PC]++);
            word address = reg[r];

            dbg("VINP\tR%u (0x%04x)", r, address);

            std::string input;
            std::getline(std::cin, input);

            if ((size_t)address + input.size() >= MEMORY_SIZE) {
                err(4, "can't fit input in memory");
            }

            for (word i = 0; i < input.size(); ++i) {
                memory[address + i] = input[i];
            }
            memory[address + input.size()] = 0x00;

            break;
        }
        case VOUT: {
            byte r = fetch_byte(reg[PC]++);
            word address = reg[r];

            dbg("VOUT\tR%u (0x%04x)", r, address);
            while (memory[address] != 0x00) {
                printf("%c", memory[address++]);
            }
            break;
        }
        default: {
            err(3, "unknown opcode: 0x%02x", opcode);
            break;
        }
        }
    }

    return 0;
}
