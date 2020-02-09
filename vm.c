#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG_TRACE

#define MEMORY_SIZE 0x7fff
#define MEMORY_ORIGIN 0x3000
#define STACK_SIZE 0x100

#define INPUT_SIZE 32

void err(int exit_code, const char* format, ...)
{
    fputs("\nfatal error: ", stderr);
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
#else
    (void)format;
#endif
}

typedef struct VM {
    uint8_t mem[MEMORY_SIZE];
    uint8_t* ip;

    short stack[STACK_SIZE];
    short* sp;

    char input[INPUT_SIZE];
    char* input_ptr;
} VM;

void vm_init(VM* vm)
{
    vm->ip = vm->mem + MEMORY_ORIGIN;
    vm->sp = vm->stack;
    vm->input_ptr = vm->input;
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

void vm_fill_input(VM* vm, char* input, int size)
{
    if (size > 32) {
        err(7, "input longer than 32");
    }

    for (int i = 0; i < size; ++i) {
        vm->input[i] = input[i];
    }
}

typedef enum Instructions {
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
} Instructions;

int vm_run(VM* vm)
{
#define READ_BYTE() (*vm->ip++)
#define READ_SHORT() (*vm->ip++ | *vm->ip++ << 8)

    for (;;) {
        dbg("$ 0x%04x\t", vm->ip - vm->mem);

        uint8_t instruction = READ_BYTE();
        switch (instruction) {
        case OP_HALT: {
            dbg("HALT");
            short value = READ_SHORT();
            dbg(" %d\n", value);
            return value;
        }
        case OP_PUSH: {
            dbg("PUSH");
            short value = READ_SHORT();
            dbg(" %d", value);
            vm_push(vm, value);
            break;
        }
        case OP_POP: {
            dbg("POP");
            short value = vm_pop(vm);
            dbg("\t\t// %d", value);
            break;
        }
        case OP_XOR: {
            dbg("XOR");
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a ^ b;
            dbg("\t\t// %d ^ %d = %d", a, b, result);
            vm_push(vm, result);
            break;
        }
        case OP_MUL: {
            dbg("MUL");
            short a = vm_pop(vm);
            short b = vm_pop(vm);
            short result = a * b;
            dbg("\t\t// %d * %d = %d", a, b, result);
            vm_push(vm, result);
            break;
        }
        case OP_INP: {
            dbg("INP");
            if (vm->input_ptr - vm->input >= INPUT_SIZE) {
                err(6, "input out of bounds");
            }
            char inp = *vm->input_ptr++;
            dbg("\t\t// %d", inp);
            if (isalpha(inp)) {
                dbg(" (%c)", inp);
            }
            vm_push(vm, inp);
            break;
        }
        case OP_JZ: {
            dbg("JZ");
            short jmp = READ_SHORT();
            dbg(" 0x%04x", jmp);
            if (vm_pop(vm) == 0) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }
        case OP_DUP: {
            dbg("DUP");
            short value = vm_pop(vm);
            dbg("\t\t// %d", value);
            vm_push(vm, value);
            vm_push(vm, value);
            break;
        }
        case OP_INC: {
            dbg("INC");
            short value = vm_pop(vm);
            short result = value + 1;
            dbg("\t\t// %d + 1 = %d", value, result);
            vm_push(vm, result);
            break;
        }
        case OP_JEMP: {
            dbg("JEMP");
            short jmp = READ_SHORT();
            dbg(" 0x%04x", jmp);
            if (vm->stack == vm->sp) {
                vm->ip = vm->mem + jmp;
            }
            break;
        }
        default: {
            err(3, "unknown instruction: %d", instruction);
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

    printf("Enter the flag: ");

    char flag[INPUT_SIZE];
    fgets(flag, sizeof(flag), stdin);
    int len = strlen(flag);
    if (flag[len - 1] == '\n') {
        flag[len - 1] = '\0';
    }
    vm_fill_input(&vm, flag, strlen(flag));

    int value = vm_run(&vm);
    if (value == 0) {
        printf("Correct flag!\n");
    } else {
        printf("Incorrect flag!\n");
    }

    return value;
}
