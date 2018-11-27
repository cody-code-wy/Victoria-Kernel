/*
 * kernel.h
 */

#pragma once


extern char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);

void
  kmain(),
  delay_random();

#ifdef TEST
void test();
#endif
