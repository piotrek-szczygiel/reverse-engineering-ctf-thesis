%include "vm.inc"

; Push the magic numbers used to check validity of the flag
push -23501
push 188
push -20983
push 269
push -24337
push 208
push -29051
push 415
push -17861
push 188
push -25705
push 504
push -30997
push 378
push -8731
push 90
push -6746
push 71
push -4256
push 37
push -31672
push 621
push -27721
push 252
push -3235
push 66
push -28225
push 392
push -5696
push 85
push -15327
push 158
push -21022
push 273
push -31541
push 332
push -30477
push 401
push -17837
push 343
push -18487
push 158
push -25521
push 220
push -24601
push 300
push -14162
push 289
push -13689
push 116
push -20419
push 166
push -27301
push 390
push -23101
push 275
push -12664
push 189
push -21415
push 258

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
