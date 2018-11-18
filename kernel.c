/*
 * kernel.c
 */

#include "kernel.h"
#include "lpt0.h"
#include "com0.h"

void kmain(void){
  const char *str = "Test Kernel";
  char *vidptr = (char*)0xb8000; //video memory begins here
  unsigned int i = 0;
  unsigned int j = 0;

  init_com0();

  while(j < 80 * 25 * 2){
    /* blnk char */
    vidptr[j] = ' ';
    /* attribute-bye - light grey on black screen */
    vidptr[j+1] = 0x2a;
    j = j + 2;
  }

  j = 0;

  while(str[j] != '\0'){
    write_com0(str[j]);
    write_lpt0(str[j]);
    vidptr[i] = str[j];
    ++j;
    i = i + 2;
  }

}

void delay_random(){
  int seconds = read_port(0x71);
  while ( seconds == read_port(0x71) );
}
