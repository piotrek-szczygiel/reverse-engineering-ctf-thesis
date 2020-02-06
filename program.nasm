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

; Initialize length counter
vset r3, 0

; Initialize current character pointer
vset r2, flag
vset r4, magic

; Do some operations on every flag character
check_loop:
vldb r0, r2
vldb r5, r4

vinc r2
vinc r3
vinc r4

; We now have current flag character in r0
; Also we have current magic character in r5


; Loop if we are not yet done checking
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
str_hello: db "Welcome to Piotr Szczygiel's CTF challenge", 10, "Enter the flag: ", 0
magic: db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
str_invalid: db "Invalid flag!", 10, 0
str_success: db "Congratulations! This is the correct flag!", 10, 0
flag:

; ~V1rTual_m4ch1n3
; [126, 86, 49, 114, 84, 117, 97, 108, 95, 109, 52, 99, 104, 49, 110, 51]
