/*
 * kernel.h
 */

#pragma once


extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

void
  kmain(),
  delay_random();
