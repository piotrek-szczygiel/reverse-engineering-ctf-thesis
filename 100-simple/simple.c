#include <stdio.h>
#include <string.h>

// Generated FLAG
#include "flag.h"

int main()
{
    char input[64];

    printf("Enter the flag: ");
    fgets(input, sizeof(input), stdin);

    input[strlen(input) - 1] = '\0';

    if (strcmp(input, FLAG) == 0) {
        puts("Correct flag!");
    } else {
        puts("Incorrect flag!");
    }

    return 0;
}