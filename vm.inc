[org 0x3000]

%macro halt 0
db 1
%endmacro

%macro push 1
db 2
dw %1
%endmacro

%macro add 0
db 3
%endmacro

%macro sub 0
db 4
%endmacro

%macro xor 0
db 5
%endmacro
