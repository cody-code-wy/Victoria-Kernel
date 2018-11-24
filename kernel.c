/*
 * kernel.c
 */

#include "kernel.h"
#include <stdint.h>
#include "lpt0.h"
#include "com0.h"

#if defined(__linux__)
#error "You are compiling a kernel to target \"linux\", this will most certainly not work"
#endif

#if !defined(__i386__)
#error "kernel.c is designed to be compiled for ix86-elf; this will not work"
#endif

void kmain(void){
  const char *str = "Test Kernel";
  char *vidptr = (char*)0xb8000; //video memory begins here
  unsigned int i = 0;
  unsigned int j = 0;

  com0_init();

  while(j < 80 * 25 * 2){
    /* blnk char */
    vidptr[j] = ' ';
    /* attribute-bye - light grey on black screen */
    vidptr[j+1] = 0x2a;
    j = j + 2;
  }

  j = 0;

  com0_write(str);
  com0_write("Write Test");

  while(str[j] != '\0'){
    com0_write_char(str[j]);
    /* write_lpt0(str[j]); */
    vidptr[i] = str[j];
    ++j;
    i = i + 2;
  }

}

void delay_random(){
  int seconds = inb(0x71);
  while ( seconds == inb(0x71) );
}
