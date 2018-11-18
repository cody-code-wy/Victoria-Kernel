/*
 * com0.h
 */

#pragma once

#include "kernel.h"

#define COM0 0x3f8 /* COM1 */

void
  init_com0(),
  write_com0( char a );

int
  com0_is_transmit_empty();
