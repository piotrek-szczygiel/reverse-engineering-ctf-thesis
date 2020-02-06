%include "vm.inc"

; Display hello message
vset r0, str_hello
vout r0

; Read flag from standard input
vset r0, flag
vinp r0

; Check if flag is 16 characters long
vset r1, 16
vcmp r0, r1
vjne invalid

vset r3, 0
vset r2, flag
check_loop:
vldb r0, r2

vinc r3
vinc r2

vnop

vcmp r3, r1
vjne check_loop

vset r0, str_success
vout r0
vhlt

; Display invalid flag message and halt
invalid:
vset r0, str_invalid
vout r0
vhlt

; Data
str_hello: db "Welcome to CTF challenge", 10, "Enter password: ", 0
magic: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
str_invalid: db "Invalid password!", 10, 0
flag: times 32 db 0
str_success: db "Congratulations! This is a correct flag!", 10, 0
