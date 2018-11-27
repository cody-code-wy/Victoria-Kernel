/*
 * kernel.c
 */

#include "kernel.h"
#include <stdint.h>
#include "stdlib.h"
#include "lpt0.h"
#include "com0.h"
#include "cterm.h"

#if defined(__linux__)
#error "You are compiling a kernel to target \"linux\", this will most certainly not work"
#endif

#if !defined(__i386__)
#error "kernel.c is designed to be compiled for ix86-elf; this will not work"
#endif

void kmain(void){

  for(int8_t i = 0; i < 9; i++)
    write_lpt0("Test LPT0"[i]);

  com0_init();

#ifdef TEST
  test();
#endif

#ifdef DEBUG
  com0_write("D> KMAIN END\n\rD> CPU HALT\n\r");
#endif
}

#ifdef TEST

void test_cterm(){
  cterm_set_text_color(VGA_COLOR_LIGHT_CYAN);
  cterm_set_background_color(VGA_COLOR_RED);
  cterm_clear();
  char itoa_buffer[4];
  for(char i = 0; i < cterm_rows; i++){
    cterm_set_cursor_pos(i,40);
    cterm_write("X <- Pos ");
    cterm_write(itoa(i,itoa_buffer,10));
    cterm_write(",40    XXXXX");
  }

  cterm_set_background_color(VGA_COLOR_WHITE);
  cterm_clear_col(59);
  cterm_clear_row(2);
  cterm_set_background_color(VGA_COLOR_GREEN);


  //Takes 1 line
  for(char i = 0; i < cterm_cols; i++){
    char c = *itoa(i%16,itoa_buffer,16);
    cterm_put_char(c, cterm_rows/2, i);
  }

  //Takes 1 line
  cterm_set_cursor_pos(13,0);
  static enum vga_color fg[16] = { 0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF };
  static enum vga_color bg[16] = { 0xF,0xE,0xD,0xC,0xB,0xA,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x2,0x1,0x0 };
  char *bltstr = "123456789ABCDEF";
  cterm_blit(bltstr,fg,bg);

  //Takes 3 lines, and 16 cols
  cterm_set_cursor_pos(14,0);
  uint8_t vga_colors[256];
  char vgabltstr[257];
  vgabltstr[256] = '\0';
  for(int color = 0; color <= 255; color++){
    vga_colors[color] = color;
    vgabltstr[color] = *itoa(color%16,itoa_buffer,16);
  }
  cterm_blit_vga(vgabltstr, vga_colors);

  //Wrap Test
  cterm_set_text_color(VGA_COLOR_LIGHT_RED);
  cterm_set_background_color(VGA_COLOR_GREY);
  cterm_set_cursor_pos(17,76);
  cterm_write("LineWrap");
  cterm_set_text_color(VGA_COLOR_LIGHT_MAGENTA);
  cterm_set_cursor_pos(24,74);
  cterm_write("ScreenWrap");
  cterm_set_cursor_pos(3,10);
  cterm_write("\nNewline Test\rCR Test");
}

void test_itoa(){
  com0_write("TEST:itoa base 10:8160543001:");
  com0_write(itoa(8160543001,"LONGENOUGHBUFFER",10));
  com0_write("\n\rTEST:itoa base 10:-8160543001:");
  com0_write(itoa(-8160543001,"LONGENOUGHBUFFER",10));
  com0_write("\n\rTEST:itoa base 16:DEADBEEF:");
  com0_write(itoa(0xdeadbeef,"LONGENOUGHBUFFER",16));
  com0_write("\n\rTEST:itoa base 2:11111000011010010111100110101011:");
  com0_write(itoa(0xF86979AB,"LONGENOUGHBUFFERFORBINARYTESTXXXXXXXX", 2));
  com0_write("\n\rTEST:ita base 36:PASS243:");
  com0_write(itoa(55072558515,"LONGENOUGBUFFER",36));
  com0_write("\n\r");
}

void test(){
  //sanity check
  com0_write("TESTING\n\r");
  com0_write("TEST:COM0_write:writetestpass:writetestpass\n\r");
  test_itoa();
  test_cterm();
}
#endif
