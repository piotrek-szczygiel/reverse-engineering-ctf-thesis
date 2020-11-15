[org 0x1337]

%macro halt 1
db 225
dw %1
%endmacro

%macro push 1
db 164
dw %1
%endmacro

%macro pop 0
db 155
%endmacro

%macro xor 0
db 3
%endmacro

%macro mul 0
db 162
%endmacro

%macro inp 0
db 177
%endmacro

%macro jz 1
db 82
dw %1
%endmacro

%macro dup 0
db 206
%endmacro

%macro inc 0
db 102
%endmacro

%macro jemp 1
db 223
dw %1
%endmacro
