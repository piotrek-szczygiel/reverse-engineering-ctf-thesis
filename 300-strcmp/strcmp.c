#include <stdio.h>
#include <string.h>

unsigned char flag[] = {

    0xb9, 0x29, 0x24, 0x49, 0x98, 0x89, 0xd2, 0xaa, 0x9e, 0xb8, 0x9e, 0x36,
    0xcd, 0xb7, 0xfe, 0xd6, 0x96, 0xa1, 0xb, 0x99, 0xf6, 0x70, 0x14, 0x3f, 0x1,
    0xb5, 0xca, 0x78, 0x50, 0x2a, 0xa0, 0xab, 0xb8, 0xa6, 0x8a
};

void decrypt_flag()
{
    for (unsigned int m = 0; m < sizeof(flag); ++m) {
        unsigned char c = flag[m];
        c -= m;
        c = ~c;
        c += m;
        c ^= 0xc7;
        c += 0x76;
        c = (c >> 0x6) | (c << 0x2);
        c -= 0x32;
        c ^= m;
        c = ~c;
        c -= 0xd6;
        c = ~c;
        c ^= 0x14;
        c -= m;
        c = -c;
        c = ~c;
        c = (c >> 0x3) | (c << 0x5);
        c -= 0xc;
        c = (c >> 0x2) | (c << 0x6);
        c ^= 0x67;
        c += m;
        c = -c;
        c += 0xe1;
        c = -c;
        c += 0x1f;
        c = ~c;
        c += 0x93;
        c = -c;
        c = (c >> 0x5) | (c << 0x3);
        c ^= 0x9b;
        c = -c;
        c = ~c;
        c += 0x14;
        c = ~c;
        c = (c >> 0x5) | (c << 0x3);
        c ^= 0xee;
        c -= 0xbb;
        c ^= m;
        c -= 0x3b;
        c = -c;
        c = (c >> 0x2) | (c << 0x6);
        c -= 0x5;
        c = (c >> 0x6) | (c << 0x2);
        c ^= 0x39;
        c += m;
        c = -c;
        c ^= 0x22;
        c += m;
        c = ~c;
        c += m;
        c ^= 0x53;
        c += m;
        c = ~c;
        c = -c;
        c += 0xf8;
        c = ~c;
        c ^= m;
        c += m;
        c = ~c;
        c += m;
        c ^= m;
        c += 0xd6;
        c ^= m;
        c = (c >> 0x6) | (c << 0x2);
        c -= 0x17;
        c = ~c;
        c ^= 0x8e;
        c += 0x4b;
        c ^= 0xa4;
        c -= m;
        c = (c >> 0x2) | (c << 0x6);
        c += m;
        c = (c >> 0x5) | (c << 0x3);
        c ^= m;
        c = -c;
        c ^= m;
        c += m;
        c = -c;
        c = ~c;
        c ^= 0x56;
        c += 0x1f;
        c ^= m;
        c = -c;
        c -= 0xcd;
        c ^= m;
        c += 0xdc;
        c = -c;
        c ^= 0x86;
        c = -c;
        c = ~c;
        c -= m;
        c ^= 0xcf;
        c += 0x66;
        c ^= 0xa7;
        c = (c >> 0x2) | (c << 0x6);
        c ^= 0xbe;
        c -= 0xf6;
        c = (c >> 0x6) | (c << 0x2);
        c -= m;
        c ^= m;
        c += 0x98;
        c ^= 0xee;
        c -= m;
        c ^= 0x8;
        c += m;
        c ^= m;
        c += m;
        c ^= 0x7c;
        c = -c;
        c = ~c;
        c += 0xa6;
        c = -c;
        c = (c >> 0x1) | (c << 0x7);
        c = ~c;
        c += m;
        c ^= m;
        c = (c >> 0x6) | (c << 0x2);
        c += 0xb7;
        c = ~c;
        c -= 0x1d;
        c ^= m;
        c -= m;
        c ^= 0xc;
        c += m;
        c = ~c;
        c ^= m;
        c += m;
        c = -c;
        c ^= m;
        flag[m] = c;
    }
}

int main()
{
    decrypt_flag();

    char input[64];

    printf("Enter the flag: ");
    fgets(input, sizeof(input), stdin);

    input[strlen(input) - 1] = '\0';

    if (strcmp(input, (char*)flag) == 0) {
        puts("Correct flag!");
    } else {
        puts("Incorrect flag!");
    }

    return 0;
}