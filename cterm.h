/*
 * cterm.h
 */

#pragma once

#include <stdint.h>

#ifdef DEBUG
#include "stdlib.h"
#include "com0.h"
char debug_buffer[18];
#endif

#define COLOR_TEXT_VIDEO_MEMORY 0xB8000
/* #define COLOR_TEXT_VIDEO_MEMORY_END 0xC8000 */
/* #define COLOR_TEXT_VIDEO_PAGE_SIZE 0x4000 */

volatile char* cterm_video;

extern const uint8_t cterm_cols;
extern const uint8_t cterm_rows;

extern uint8_t cterm_cursor_col;
extern uint8_t cterm_cursor_row;

extern uint8_t cterm_current_vga_color;

enum vga_color {
  VGA_COLOR_BLACK = 0x0,
  VGA_COLOR_BLUE = 0x1,
  VGA_COLOR_GREEN = 0x2,
  VGA_COLOR_CYAN = 0x3,
  VGA_COLOR_RED = 0x4,
  VGA_COLOR_MAGENTA = 0x5,
  VGA_COLOR_BROWN = 0x6,
  VGA_COLOR_LIGHT_GREY = 0x7, //Dark White
  VGA_COLOR_GREY = 0x8, //Light Black
  VGA_COLOR_LIGHT_BLUE = 0x9,
  VGA_COLOR_LIGHT_GREEN = 0xA,
  VGA_COLOR_LIGHT_CYAN = 0xB,
  VGA_COLOR_LIGHT_RED = 0xC,
  VGA_COLOR_LIGHT_MAGENTA = 0xD,
  VGA_COLOR_LIGHT_BROWN = 0xE,
  VGA_COLOR_WHITE = 0xF,
};

void
  cterm_advance_line(),
  cterm_advance_cursor(),
  cterm_write_char( char a ),
  cterm_write_cstr( const char* a ),
  cterm_write( char* str ),
  cterm_put_char( char a, uint8_t row, uint8_t col ),
  cterm_blit( char* str, enum vga_color* fg, enum vga_color* bg),
  cterm_blit_vga( char * str, uint8_t* colors ),
  cterm_clear(),
  cterm_clear_row( uint8_t row ),
  cterm_clear_cursor_row(),
  cterm_clear_col( uint8_t col ),
  cterm_clear_cursor_col(),
  cterm_get_cursor_pos( uint8_t* row, uint8_t* col ),
  cterm_set_cursor_pos( uint8_t row, uint8_t col ),
  //cterm_set_cursor_blink( bool blink ),
  cterm_get_size( uint8_t* rows, uint8_t* cols ),
  //cterm_scroll( uint8_t n ),
  cterm_set_text_color( enum vga_color c ),
  cterm_set_background_color( enum vga_color c ),
  cterm_set_vga_color( uint8_t color );
  /* cterm_set_current_page( uint8_t page ), */
  /* cterm_move_pages( uint8_t source_page, uint8 destination_page ), */
  /* cterm_copy_page_to_a( uint8_t source_page, char* destination_a, int a_len ), */
  /* cterm_copy_a_to_page( char* source_a, int a_len, uint8_t destination_page ); */

uint8_t
  cterm_build_color( enum vga_color fg, enum vga_color bg );
  /* cterm_get_current_page(), */
  /* cterm_get_page_count(); */

uint16_t
  cterm_get_buffer_offset();

enum vga_color
  cterm_get_text_color(),
  cterm_get_background_color();
