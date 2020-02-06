%include "vm.inc"

vset r0, str_hello
vout r0

vset r0, flag
vinp r0

vset r1, 16
vcmp r0, r1

vjne invalid
vhlt

invalid:
vset r0, str_invalid
vout r0
vhlt

str_hello: db "Welcome to CTF challenge", 0x0a, "Enter password: ", 0x00
str_invalid: db "Invalid password!", 0x0a, 0x00

flag: times 32 db 0
