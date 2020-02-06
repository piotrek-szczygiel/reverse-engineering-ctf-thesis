%include "vm.inc"

vset r0, hello
vout r0

vhlt

hello: db "Welcome to CTF challenge", 0x0a, "Enter password: ", 0x00
