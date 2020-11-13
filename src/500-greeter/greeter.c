#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void get_secret_shell()
{
    system("/bin/sh");
}

void greeter()
{
    char name[256];

    printf("Enter your name: ");
    gets(name);
    printf("Hello, %s!\n", name);
}

int main()
{
    gid_t gid;
    uid_t uid;
    gid = getegid();
    uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    greeter();
    return 0;
}