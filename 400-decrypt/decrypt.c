#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char flag[] = { 0x90, 0xf9, 0xeb, 0x94, 0xaf, 0xdf, 0xce, 0x8a, 0xb2, 0xce,
    0xd9, 0x99, 0xbf, 0xd9, 0xe1, 0x88, 0xab, 0xdf, 0xe1, 0x9d, 0xbf, 0xdd,
    0xdb, 0x83, 0xbd, 0xca, 0xcc, 0x9e, 0x81, 0x95, 0x87, 0xd7, 0xee, 0xd0 };

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
    printf("Enter the flag: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "unable to read flag from stdin\n");
        return 1;
    }

    int length = strlen(input) - 1;
    input[length] = '\0';

    if (length == sizeof(flag)) {
        encrypt(input, strlen(input));

        bool same = true;
        for (int i = 0; i < length; ++i) {
            if (input[i] != flag[i]) {
                same = false;
                break;
            }
        }

        if (same) {
            printf("\x1b[92;1mCorrect flag!\x1b[0m\n");
            return 0;
        }
    }

    printf("\x1b[91;1mIncorrect flag!\x1b[0m\n");
    return 0;
}