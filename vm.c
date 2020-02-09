#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_TRACE

#define MEMORY_SIZE 0x7fff
#define MEMORY_ORIGIN 0x3000
#define STACK_SIZE 0x100

void err(int exit_code, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);
    exit(exit_code);
}

void dbg(const char* format, ...)
{
#ifdef DEBUG_TRACE
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
#endif
}

typedef struct VM {
    uint8_t mem[MEMORY_SIZE];
    uint8_t* ip;

    short stack[STACK_SIZE];
    short* sp;
} VM;

void vm_init(VM* vm)
{
    vm->ip = vm->mem + MEMORY_ORIGIN;
    memset(vm->mem, 0, MEMORY_SIZE);

    vm->sp = vm->stack;
    memset(vm->stack, 0, STACK_SIZE);
}

void vm_load(VM* vm, const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        err(2, "unable to open file: %s", filename);
    }

    int read = fread(vm->mem + MEMORY_ORIGIN, 1, MEMORY_SIZE, file);
    dbg("read %d bytes from %s\n", read, filename);

    fclose(file);
}

void vm_push(VM* vm, short value)
{
    if (vm->sp - vm->stack >= STACK_SIZE) {
        err(4, "stack overflow");
    }

    *vm->sp++ = value;
}

short vm_pop(VM* vm)
{
    if (vm->sp == vm->stack) {
        err(5, "unable to pop from empty stack");
    }

    return *--vm->sp;
}

typedef enum Instructions {
    OP_HALT = 1,
    OP_PUSH = 2,
    OP_ADD = 3,
    OP_SUB = 4,
    OP_XOR = 5,
} Instructions;

void vm_run(VM* vm)
{
#define READ_BYTE() (*vm->ip++)
#define READ_SHORT() (*vm->ip++ | *vm->ip++ << 8)

    bool running = true;

    while (running) {
        dbg("$ 0x%04x\t", vm->ip - vm->mem);

        uint8_t instruction = READ_BYTE();
        switch (instruction) {
        case OP_HALT: {
            dbg("HALT");
            running = false;
            break;
        }
        case OP_PUSH: {
            short value = READ_SHORT();
            dbg("PUSH %d", value);
            vm_push(vm, value);
            break;
        }
        case OP_ADD: {
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a + b;
            vm_push(vm, result);
            dbg("ADD\t\t// %d + %d = %d", a, b, result);
            break;
        }
        case OP_SUB: {
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a - b;
            vm_push(vm, result);
            dbg("SUB\t\t// %d - %d = %d", a, b, result);
            break;
        }
        case OP_XOR: {
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a ^ b;
            vm_push(vm, result);
            dbg("XOR\t\t// %d ^ %d = %d", a, b, result);
            break;
        }
        default: {
            err(3, "unknown instruction: %d", instruction);
            running = false;
            break;
        }
        }

        dbg("\n");
    }

#undef READ_BYTE
#undef READ_SHORT
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        err(1, "usage: %s rom_file", argv[0]);
    }

    VM vm;
    vm_init(&vm);
    vm_load(&vm, argv[1]);
    vm_run(&vm);

    return 0;
}
