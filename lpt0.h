/*
 * lpt0.h
 */

#pragma once

#include "kernel.h"

#define LPT0 0x378 /* LPT0 */

void
  strobe_lpt0(),
  set_lpt0_control( unsigned short control ),
  write_lpt0( char a );

int
  is_lpt0_busy();

unsigned short
  get_lpt0_control();
