#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generated header file containing ROM char array
#include "ctf.h"

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
}

void vm_push(VM* vm, short value)
{
    if (vm->sp - vm->stack >= STACK_SIZE) {
        exit(3);
    }

    *vm->sp++ = value;
}

short vm_pop(VM* vm)
{
    if (vm->sp == vm->stack) {
        exit(4);
    }

    return *--vm->sp;
}

void vm_fill_input(VM* vm, const char* input, int size)
{
    if (size > INPUT_SIZE) {
        exit(5);
    }

    for (int i = 0; i < size; ++i) {
        vm->input[i] = input[i];
    }
}

uint8_t vm_read_byte(VM* vm)
{
    return *vm->ip++;
}

short vm_read_short(VM* vm)
{
    vm->ip += 2;
    return *(vm->ip - 2) | *(vm->ip - 1) << 8;
}

int vm_run(VM* vm)
{
    for (;;) {
        uint8_t opcode = vm_read_byte(vm);

        switch (opcode) {
        // Halt the program with a return value
        case OP_HALT: {
            short value = vm_read_short(vm);
            return value;
        }

        // Push immediate value on the stack
        case OP_PUSH: {
            short value = vm_read_short(vm);
            vm_push(vm, value);
            break;
        }

        // Pop value from the stack (and discard it)
        case OP_POP: {
            vm_pop(vm);
            break;
        }

        // XOR values on the stack
        case OP_XOR: {
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a ^ b;
            vm_push(vm, result);
            break;
        }

        // Multiply values on the stack
        case OP_MUL: {
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a * b;
            vm_push(vm, result);
            break;
        }

        // Push next letter on the stack from the input buffer
        case OP_INP: {
            if (vm->input_ptr - vm->input >= INPUT_SIZE) {
                exit(6);
            }
            uint8_t inp = *vm->input_ptr++;
            vm_push(vm, inp);
            break;
        }

        // Jump to given address if popped value is equal to zero
        case OP_JZ: {
            short jmp = vm_read_short(vm);
            if (vm_pop(vm) == 0) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }

        // Duplicate first value on the stack
        case OP_DUP: {
            short value = vm_pop(vm);
            vm_push(vm, value);
            vm_push(vm, value);
            break;
        }

        // Increment first value on the stack
        case OP_INC: {
            short value = vm_pop(vm);
            short result = value + 1;
            vm_push(vm, result);
            break;
        }

        // Jump to given address if stack is empty
        case OP_JEMP: {
            short jmp = vm_read_short(vm);
            if (vm->stack == vm->sp) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }

        // Crash the VM if invalid instruction is read
        default: {
            exit(2);
        }
        }
    }
}

VM vm;
int main()
{
    vm_init(&vm);
    vm_load(&vm, ctf_rom, ctf_rom_len);

    char flag[INPUT_SIZE];

    printf("Enter the flag: ");
    fgets(flag, sizeof(flag), stdin);

    flag[strlen(flag) - 1] = '\0';
    vm_fill_input(&vm, flag, strlen(flag));

    int result = vm_run(&vm);

    if (result == 0) {
        puts("Correct flag!");
    } else {
        puts("Incorrect flag!");
    }

    return result;
}
