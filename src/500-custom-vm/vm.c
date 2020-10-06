#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generated header file containing ROM char array
#include "ctf.h"

// Uncomment the line below if you want to see disassembly output
// #define DEBUG_TRACE

void err(int exit_code, const char* format, ...)
{
#ifdef DEBUG_TRACE
    fputs("\nfatal error: ", stderr);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);
#else
    (void)format;
#endif
    exit(exit_code);
}

void dbg(const char* format, ...)
{
#ifdef DEBUG_TRACE
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
#else
    (void)format;
#endif
}

void ascii_art_logo()
{
    printf("\x1b[96m");
    printf("                                      _      __        __  ____\n"
           "   _________  _________  __  ______ _(_)__  / /  _____/ /_/ __/\n"
           "  / ___/_  / / ___/_  / / / / / __ `/ / _ \\/ /  / ___/ __/ /_\n"
           " (__  ) / /_/ /__  / /_/ /_/ / /_/ / /  __/ /  / /__/ /_/ __/\n"
           "/____/ /___/\\___/ /___/\\__, /\\__, /_/\\___/_/   \\___/\\__/_/\n"
           "                      /____//____/               \x1b[97;1m2020");
    printf("\x1b[0m\n\n");
}

#define MEMORY_SIZE 0x7fff
#define MEMORY_ORIGIN 0x1337
#define STACK_SIZE 0x0100
#define INPUT_SIZE 128

typedef struct VM {
    uint8_t mem[MEMORY_SIZE];
    uint8_t* ip;

    short stack[STACK_SIZE];
    short* sp;

    uint8_t input[INPUT_SIZE];
    uint8_t* input_ptr;
} VM;

typedef enum Opcode {
    OP_HALT = 225,
    OP_PUSH = 164,
    OP_POP = 155,
    OP_XOR = 3,
    OP_MUL = 162,
    OP_INP = 177,
    OP_JZ = 82,
    OP_DUP = 206,
    OP_INC = 102,
    OP_JEMP = 223,
} Opcode;

void vm_init(VM* vm)
{
    vm->ip = vm->mem + MEMORY_ORIGIN;
    vm->sp = vm->stack;
    vm->input_ptr = vm->input;
}

void vm_load(VM* vm, const uint8_t* rom, size_t rom_size)
{
    memcpy(vm->mem + MEMORY_ORIGIN, rom, rom_size);
    dbg("loaded %zu bytes into vm\n", rom_size);
}

void vm_push(VM* vm, short value)
{
    if (vm->sp - vm->stack >= STACK_SIZE) {
        err(3, "stack overflow");
    }

    *vm->sp++ = value;
}

short vm_pop(VM* vm)
{
    if (vm->sp == vm->stack) {
        err(4, "pop from empty stack");
    }

    return *--vm->sp;
}

void vm_fill_input(VM* vm, const char* input, int size)
{
    if (size > INPUT_SIZE) {
        err(5, "input longer than %d", INPUT_SIZE);
    }

    for (int i = 0; i < size; ++i) {
        vm->input[i] = input[i];
    }
}

inline uint8_t vm_read_byte(VM* vm)
{
    return *vm->ip++;
}

inline short vm_read_short(VM* vm)
{
    vm->ip += 2;
    return *(vm->ip - 2) | *(vm->ip - 1) << 8;
}

int vm_run(VM* vm)
{
    for (;;) {
        dbg("\x1b[97;1m0x%04x\t\x1b[0m", vm->ip - vm->mem);
        uint8_t opcode = vm_read_byte(vm);

        switch (opcode) {
        // Halt the program with a return value
        case OP_HALT: {
            dbg("HALT");
            short value = vm_read_short(vm);
            dbg(" %d\n", value);
            return value;
        }

        // Push immediate value on the stack
        case OP_PUSH: {
            dbg("PUSH");
            short value = vm_read_short(vm);
            dbg(" %d", value);
            vm_push(vm, value);
            break;
        }

        // Pop value from the stack (and discard it)
        case OP_POP: {
            dbg("POP");
            vm_pop(vm);
            break;
        }

        // XOR values on the stack
        case OP_XOR: {
            dbg("XOR");
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a ^ b;
            dbg("\t\t\x1b[32m// %d ^ %d = %d", a, b, result);
            vm_push(vm, result);
            break;
        }

        // Multiply values on the stack
        case OP_MUL: {
            dbg("MUL");
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a * b;
            dbg("\t\t\x1b[32m// %d * %d = %d", a, b, result);
            vm_push(vm, result);
            break;
        }

        // Push next letter on the stack from the input buffer
        case OP_INP: {
            dbg("INP");
            if (vm->input_ptr - vm->input >= INPUT_SIZE) {
                err(6, "input out of bounds");
            }
            uint8_t inp = *vm->input_ptr++;
            dbg("\t\t\x1b[32m// %d", inp);
            if (isalpha(inp)) {
                dbg(" (%c)", inp);
            }
            vm_push(vm, inp);
            break;
        }

        // Jump to given address if popped value is equal to zero
        case OP_JZ: {
            dbg("JZ");
            short jmp = vm_read_short(vm);
            dbg(" 0x%04x", jmp);
            if (vm_pop(vm) == 0) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }

        // Duplicate first value on the stack
        case OP_DUP: {
            dbg("DUP");
            short value = vm_pop(vm);
            dbg("\t\t\x1b[32m// %d", value);
            vm_push(vm, value);
            vm_push(vm, value);
            break;
        }

        // Increment first value on the stack
        case OP_INC: {
            dbg("INC");
            short value = vm_pop(vm);
            short result = value + 1;
            dbg("\t\t\x1b[32m// %d + 1 = %d", value, result);
            vm_push(vm, result);
            break;
        }

        // Jump to given address if stack is empty
        case OP_JEMP: {
            dbg("JEMP");
            short jmp = vm_read_short(vm);
            dbg(" 0x%04x", jmp);
            if (vm->stack == vm->sp) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }

        // Crash the VM if invalid instruction is read
        default: {
            err(2, "unknown opcode: %d", opcode);
        }
        }

        dbg("\n\x1b[0m");
    }
}

VM vm;
int main()
{
    ascii_art_logo();

    vm_init(&vm);
    vm_load(&vm, ctf_rom, ctf_rom_len);

    printf("Enter the flag: ");

    printf("\x1b[33m");
    char flag[INPUT_SIZE];
    if (fgets(flag, sizeof(flag), stdin) == NULL) {
        err(1, "unable to read flag from stdin");
    }
    printf("\x1b[0m");

    flag[strlen(flag) - 1] = '\0';
    vm_fill_input(&vm, flag, strlen(flag));

    int result = vm_run(&vm);

    if (result == 0) {
        printf("\x1b[92;1mCorrect flag!\x1b[0m\n");
    } else {
        printf("\x1b[91;1mIncorrect flag!\x1b[0m\n");
    }

    return result;
}
