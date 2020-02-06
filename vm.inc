[org 0x3000]

%define r0 0
%define r1 1

%macro vnop 0
db 0xde
%endmacro

%macro vhlt 0
db 0x00
%endmacro

%macro vset 2
db 0x17, %1
dw %2
%endmacro

%macro vinp 1
db 0xe9, %1
%endmacro

%macro vout 1
db 0xb3, %1
%endmacro

%macro vcmp 2
db 0x44, %1, %2
%endmacro

%macro vje 1
db 0xa1
dw %1
%endmacro

%macro vjne 1
db 0x99
dw %1
%endmacro
