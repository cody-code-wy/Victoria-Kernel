/*
 * lpt0.c
 */

#include "lpt0.h"

void strobe_lpt0() {
  unsigned short lcontrol = get_lpt0_control();
  set_lpt0_control(lcontrol | 1);
  set_lpt0_control(lcontrol & 0xfe);
}

void set_lpt0_control(unsigned short control){
  outb(LPT0 + 2, control);
}

void write_lpt0(char a){
  while (is_lpt0_busy() == 0);
  outb(LPT0, a);
  strobe_lpt0();
}

int is_lpt0_busy() {
  return inb(LPT0 + 1) & 0x80;
}

unsigned short get_lpt0_control(){
  return inb(LPT0 + 2);
}
