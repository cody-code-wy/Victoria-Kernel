/*
 * com0.h
 */

#pragma once

#include "kernel.h"

#define COM0 0x3f8 /* COM1 */

void
  com0_init(),
  com0_write_char( char a ),
  com0_write( const char* str );

int
  com0_is_transmit_empty();
