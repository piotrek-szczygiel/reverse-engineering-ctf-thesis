#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define GRAY "90"
#define RED "91"
#define GREEN "92"
#define GOLD "93"
#define CYAN "96"

void set_color(const char* color)
{
    printf("\033[%sm", color);
}

void reset_color()
{
    printf("\033[0m");
}

void print_effect(const char* s, const char* color, int times)
{
    int l = strlen(s);

    for (int i = 0; i < times; ++i) {
        printf("\0337"); // Save cursor position
        for (int j = 0; j < l; ++j) {
            putchar(33 + (rand() % 94)); // Random printable ASCII character
            usleep(2000 * (1 + rand() % 5));
        }
        printf("\0338"); // Restore cursor position
    }

    set_color(color);
    for (int i = 0; i < l; ++i) {
        putchar(s[i]);
        usleep(2000 * (1 + rand() % 8));
    }
    reset_color();
}

void greeter()
{
    char name[64];

    print_effect("Welcome, enter your name: ", GRAY, 3);
    gets(name);
    print_effect("Hello, ", GRAY, 2);
    print_effect(name, GOLD, 3);
    printf("\n\n");
}

void access_secret_shell()
{
    print_effect("Welcome to secret shell!", GRAY, 3);
    printf("\n");

    system("/bin/sh");

    print_effect("Exiting secret shell...", GRAY, 3);
    printf("\n");
}

int main()
{
    gid_t gid;
    uid_t uid;
    gid = getegid();
    uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));

    greeter();

    char access_code[64];
    FILE* file = fopen("/home/admin/access_code.txt", "r");
    if (file == NULL) {
        return 1;
    }
    fgets(access_code, sizeof(access_code), file);
    fclose(file);

    char input[64];

    while (true) {
        print_effect("Enter the access code: ", GRAY, 3);
        set_color(CYAN);
        fgets(input, sizeof(input), stdin);
        reset_color();

        if (strcmp(access_code, input) == 0) {
            print_effect("Access granted!", GREEN, 2);
            printf("\n\n");
            access_secret_shell();
            break;
        } else {
            print_effect("Access denied!", RED, 2);
            printf("\n\n");
        }
    }

    return 0;
}