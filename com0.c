/*
 * com0.c
 */

#include "com0.h"

void init_com0() {
  write_port(COM0 + 1, 0x00); /// Disable all interrupts
  write_port(COM0 + 3, 0x80); /// Enable DLAB (set baud rate divisor)
  write_port(COM0 + 0, 0x03); /// set divisor to 3 (lo byte) 38400 baud
  write_port(COM0 + 1, 0x00); ///                  (hi byte)
  write_port(COM0 + 3, 0x03); /// 8 bits, no parity, one stop bit
  write_port(COM0 + 2, 0xC7); /// Enable FIFO, clear them, with 14-byte threshold
  write_port(COM0 + 4, 0x0B); /// IRQs enbaled, RTS/BSR set
}

void write_com0(char a){
  while (com0_is_transmit_empty() == 0);
  write_port(COM0,a);
}


int com0_is_transmit_empty() {
  return read_port(COM0 + 5) & 0x20;
}
