/*
 * kernel.c
 */

#include "kernel.h"
#include <stdint.h>
#include "stdlib.h"
#include "lpt0.h"
#include "com0.h"

#if defined(__linux__)
#error "You are compiling a kernel to target \"linux\", this will most certainly not work"
#endif

#if !defined(__i386__)
#error "kernel.c is designed to be compiled for ix86-elf; this will not work"
#endif

void kmain(void){

  for(int8_t i = 0; i < 9; i++)
    write_lpt0("Test LPT0"[i]);

  com0_init();

  //sanity check
  com0_write("TESTING\n\r");
  com0_write("TEST:COM0_write:writetestpass:writetestpass\n\r");
  //itoa
  com0_write("TEST:itoa base 10:8160543001:");
  com0_write(itoa(8160543001,"LONGENOUGHBUFFER",10));
  com0_write("\n\rTEST:itoa base 10:-8160543001:");
  com0_write(itoa(-8160543001,"LONGENOUGHBUFFER",10));
  com0_write("\n\rTEST:itoa base 16:DEADBEEF:");
  com0_write(itoa(0xdeadbeef,"LONGENOUGHBUFFER",16));
  com0_write("\n\rTEST:itoa base 2:11111000011010010111100110101011:");
  com0_write(itoa(0xF86979AB,"LONGENOUGHBUFFERFORBINARYTESTXXXXXXXX", 2));
  com0_write("\n\rTEST:ita base 36:PASS243:");
  com0_write(itoa(55072558515,"LONGENOUGBUFFER",36));
}

void delay_random(){
  int seconds = inb(0x71);
  while ( seconds == inb(0x71) );
}
