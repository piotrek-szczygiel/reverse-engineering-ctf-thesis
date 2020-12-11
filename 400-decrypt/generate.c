#include <stdio.h>
#include <string.h>

void encrypt(char* input, int length)
{
    for (int i = 0; i < length; ++i) {
        char c = input[i];

        if (c >= 'A' && c <= 'Z') {
            if (c + 13 <= 'Z')
                input[i] = c + 13;
            else
                input[i] = c - 13;
        } else if (c >= 'a' && c <= 'z') {
            if (c + 13 <= 'z')
                input[i] = c + 13;
            else
                input[i] = c - 13;
        }
    }

    char key[] = { 0xde, 0xad, 0xbe, 0xef };
    int k = 0;

    for (int i = 0; i < length; ++i) {
        input[i] ^= key[k];
        k = (k + 1) % sizeof(key);
    }
}

int main()
{
    char input[64];
    fgets(input, sizeof(input), stdin);

    int length = strlen(input) - 1;
    input[length] = '\0';

    encrypt(input, length);

    for (int i = 0; i < length; ++i) {
        printf("0x%02x, ", (unsigned char)input[i]);
    }

    return 0;
}