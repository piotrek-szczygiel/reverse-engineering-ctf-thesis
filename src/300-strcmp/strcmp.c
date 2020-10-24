#include <stdio.h>
#include <string.h>

unsigned char flag[] = {

    0x2c, 0xe0, 0xbc, 0x6b, 0x33, 0x57, 0x98, 0x54, 0x91, 0xa0, 0x85, 0xd0,
    0xdc, 0x4d, 0x5, 0xd3, 0xcb, 0x4f, 0x21, 0x24, 0x21, 0x5f, 0x8b, 0xd6, 0x75,
    0x7b, 0xd0, 0x9e, 0xcc, 0xdd, 0xac, 0x5f, 0xc2
};

void decrypt_flag()
{
    for (unsigned int m = 0; m < sizeof(flag); ++m) {
        unsigned char c = flag[m];
        c ^= m;
        c -= 0xfa;
        c ^= 0xf6;
        c = ~c;
        c -= 0x9e;
        c = -c;
        c -= m;
        c = (c >> 0x2) | (c << 0x6);
        c -= m;
        c = ~c;
        c = -c;
        c ^= m;
        c += m;
        c ^= m;
        c += 0x53;
        c ^= 0x67;
        c += 0xd9;
        c = (c >> 0x5) | (c << 0x3);
        c += 0x43;
        c ^= m;
        c -= 0x8d;
        c = ~c;
        c -= m;
        c = (c >> 0x2) | (c << 0x6);
        c += 0x15;
        c = ~c;
        c = (c >> 0x1) | (c << 0x7);
        c = ~c;
        c += m;
        c = ~c;
        c -= m;
        c = ~c;
        c -= m;
        c = (c >> 0x6) | (c << 0x2);
        c += m;
        c ^= 0x49;
        c += m;
        c = (c >> 0x5) | (c << 0x3);
        c ^= m;
        c = (c >> 0x2) | (c << 0x6);
        c ^= m;
        c = (c >> 0x1) | (c << 0x7);
        c ^= m;
        c += 0x5b;
        c ^= m;
        c += m;
        c = ~c;
        c += m;
        c ^= m;
        c -= 0x88;
        c = (c >> 0x6) | (c << 0x2);
        c ^= 0xac;
        c -= 0x4b;
        c = -c;
        c += 0xe7;
        c ^= 0x14;
        c = -c;
        c += 0xf4;
        c = (c >> 0x3) | (c << 0x5);
        c += m;
        c = -c;
        c = ~c;
        c = (c >> 0x2) | (c << 0x6);
        c += m;
        c = ~c;
        c ^= m;
        c = ~c;
        c += m;
        c ^= 0xd3;
        c -= m;
        c = -c;
        c = (c >> 0x3) | (c << 0x5);
        c = -c;
        c ^= 0x7e;
        c -= 0xa2;
        c = (c >> 0x1) | (c << 0x7);
        c -= 0x87;
        c = -c;
        c += m;
        c = -c;
        c += 0x33;
        c = -c;
        c += m;
        c = (c >> 0x6) | (c << 0x2);
        c -= m;
        c ^= 0xb2;
        c += m;
        c = ~c;
        c = (c >> 0x3) | (c << 0x5);
        c += 0xec;
        c ^= 0x1f;
        c -= m;
        c ^= m;
        c += 0x43;
        c = -c;
        c ^= m;
        c += 0xdf;
        c ^= m;
        c = (c >> 0x5) | (c << 0x3);
        c += 0x62;
        c = -c;
        c += 0x5b;
        c = (c >> 0x1) | (c << 0x7);
        c += 0x49;
        c ^= 0xb6;
        c = (c >> 0x3) | (c << 0x5);
        c ^= 0x7d;
        c = -c;
        c -= 0x4f;
        c = (c >> 0x7) | (c << 0x1);
        c ^= 0x47;
        c += 0x1c;
        c = ~c;
        c += 0xd6;
        c = ~c;
        c = -c;
        c ^= 0x85;
        c = (c >> 0x7) | (c << 0x1);
        c -= m;
        c ^= m;
        c = ~c;
        c = -c;
        c += 0xb4;
        c = ~c;
        c -= m;
        c = -c;
        c = ~c;
        c += 0xdd;
        flag[m] = c;
    }
}

int main()
{
    decrypt_flag();

    char input[64];
    printf("Enter the flag: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "unable to read flag from stdin\n");
        return 1;
    }

    input[strlen(input) - 1] = '\0';

    if (strcmp(input, (char*)flag) == 0) {
        printf("\x1b[92;1mCorrect flag!\x1b[0m\n");
    } else {
        printf("\x1b[91;1mIncorrect flag!\x1b[0m\n");
    }

    return 0;
}