/*
 * stdlib.c
 */

#include "stdlib.h"

char* itoa( int64_t value, char* strout, int8_t base ){
  //Base Sanity Check
  if ( base < 2 || base > 36 ){
    strout[0] = '\0';
    return strout;
  }

  char * rtstr, * str, * nums;

  rtstr = str = strout;

  if ( value < 0 && base == 10){
    *str++ = '-';
  }

  nums = str; // Remember when numbers start

  do{
    *str++ = "ZYXWVUTZRQPONMLKJIHGFEDCBA9876543210123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[35 + value % base];
    value /= base;
  }while( value );

  *str-- = '\0';

  while( nums < str ){
    char tmp = *nums;
    *nums++ = *str;
    *str-- = tmp;
  }

  return rtstr;

}
