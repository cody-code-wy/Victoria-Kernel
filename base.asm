;;kernel.asm
bits 32       ;nasm directive - 32 bit
section .text
    ;multiboot spec
    align 4
    dd 0x1BADB002       ;magic
    dd 0x00             ;flags
    dd - (0x1BADB002 + 0x00) ;checksum m+f+c should be zero

global start
global inb
global outb
extern kmain

start:
  cli                   ;block interrupts
  mov esp, stack_space  ;set stack pointer
  call kmain
  cli
.hang:
  hlt                   ;halt
  jmp .hang


inb:
  mov edx, [esp + 4]    ;set port
  in al, dx             ;read port
  ret

outb:
  mov edx, [esp + 4]    ;set port
  mov al, [esp + 4 + 4]            ;write to portO
  out dx, al
  ret

section .bss
resb 8192               ;8KB for stack
stack_space:
