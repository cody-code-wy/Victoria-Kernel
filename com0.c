/*
 * com0.c
 */

#include "com0.h"
#include <stdint.h>

void com0_init() {
  outb(COM0 + 1, 0x00); /// Disable all interrupts
  outb(COM0 + 3, 0x80); /// Enable DLAB (set baud rate divisor)
  outb(COM0 + 0, 0x03); /// set divisor to 3 (lo byte) 38400 baud
  outb(COM0 + 1, 0x00); ///                  (hi byte)
  outb(COM0 + 3, 0x03); /// 8 bits, no parity, one stop bit
  outb(COM0 + 2, 0xC7); /// Enable FIFO, clear them, with 14-byte threshold
  outb(COM0 + 4, 0x0B); /// IRQs enbaled, RTS/BSR set
}

void com0_write_char(char a){
  while (com0_is_transmit_empty() == 0);
  outb(COM0,a);
}

void com0_write(const char* str){
  for(uint16_t i = 0; str[i] != '\0'; i++)
    com0_write_char(str[i]);
}


int com0_is_transmit_empty() {
  return inb(COM0 + 5) & 0x20;
}
