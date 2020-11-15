#include <stdio.h>
#include <string.h>

// Generated FLAG
#include "flag.h"

int main()
{
    char input[64];
    printf("Enter the flag: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "unable to read flag from stdin\n");
        return 1;
    }

    input[strlen(input) - 1] = '\0';

    if (strcmp(input, FLAG) == 0) {
        printf("\x1b[92;1mCorrect flag!\x1b[0m\n");
    } else {
        printf("\x1b[91;1mIncorrect flag!\x1b[0m\n");
    }

    return 0;
}