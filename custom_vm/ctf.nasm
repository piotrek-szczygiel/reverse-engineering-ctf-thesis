%include "vm.inc"

; Push the magic numbers used to check validity of the flag onto the stack
%include "ctf.push"

; Validation loop
check_loop:
inp
dup
jz maybe
mul
xor
inc
jz check_loop

; Invalid character
bad:
halt 1

; All checked characters valid, but maybe not long enough
maybe:
pop
jemp good
halt 1

; All characters valid, and length is the same
good:
halt 0
