/*
 * lpt0.c
 */

#include "lpt0.h"

void strobe_lpt0() {
  unsigned short lcontrol = get_lpt0_control();
  set_lpt0_control(lcontrol | 1);
  delay_random();
  set_lpt0_control(lcontrol & 0xfe);
}

void set_lpt0_control(unsigned short control){
  write_port(LPT0 + 2, control);
}

void write_lpt0(char a){
  while (is_lpt0_busy() == 0);
  write_port(LPT0, a);
  strobe_lpt0();
}

int is_lpt0_busy() {
  return read_port(LPT0 + 1) & 0x80;
}

unsigned short get_lpt0_control(){
  return read_port(LPT0 + 2);
}
