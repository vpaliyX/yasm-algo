%define stdin       0
%define stdout      1
%define stderr      2

%define SYS_nosys   0x2000000
%define SYS_exit    0x2000001
%define SYS_fork    0x2000002
%define SYS_read    0x2000003
%define SYS_write   0x2000004
%define SYS_open    0x2000005
%define SYS_close   0x2000006
%define SYS_brk     0x2000045

section .text
  bits 64
  extern _scanf
  extern _printf
  align 4
  access.the.osx.kernel:
  syscall
  ret

%macro  system  1
  mov rax, %1
  call access.the.osx.kernel
%endmacro

%macro in 2
  push rdi
  push rsi
  mov rdi, %1
  mov rsi, %2
  call _scanf
  xor rax, rax
  pop rsi
  pop rdi
%endmacro

%macro out 2
  push rdi
  push rsi
  mov rdi, %1
  mov rsi, %2
  xor rax, rax
  call _printf
  xor rax, rax
  pop rsi
  pop rdi
%endmacro

%macro  sys.exit    0
  system  SYS_exit
%endmacro

%macro  sys.write   0
  system  SYS_write
%endmacro
