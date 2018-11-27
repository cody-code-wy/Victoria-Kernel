/*
 * cterm.c
 */

#include "cterm.h"

volatile char* cterm_video = (volatile char*)COLOR_TEXT_VIDEO_MEMORY;

const uint8_t cterm_cols = 80;
const uint8_t cterm_rows = 25;

uint8_t cterm_cursor_col = 0;
uint8_t cterm_cursor_row = 0;

uint8_t cterm_current_vga_color = 0x0F;

void cterm_advance_line(){
  cterm_cursor_row++;
  if ( cterm_cursor_row >= cterm_rows ){
    cterm_cursor_row = 0; //Screen Wrap
  }
}

void cterm_advance_cursor(){
#ifdef DEBUG
  com0_write("D> ---VVV--- cterm_advance_cursor ---VVV---\n\r");
  com0_write("cursor: col:");
  com0_write(itoa(cterm_cursor_col,debug_buffer,10));
  com0_write(" row:");
  com0_write(itoa(cterm_cursor_row,debug_buffer,10));
  com0_write("\n\r");
#endif
  cterm_cursor_col++;
  if ( cterm_cursor_col >= cterm_cols ){
    cterm_cursor_col = 0; //Line Wrap
    cterm_advance_line();
  }
#ifdef DEBUG
  com0_write("D> ---^^^--- cterm_advance_cursor ---^^^---\n\r");
#endif
}

void cterm_write_char( char a ){
  uint16_t buff_offset = cterm_get_buffer_offset();
#ifdef DEBUG
  com0_write("D> ---VVV--- cterm_write_char ---VVV---\n\r");
  com0_write("char:");
  com0_write_char(a);
  com0_write(" cursor_col:");
  com0_write(itoa(cterm_cursor_col,debug_buffer,10));
  com0_write(" cursor_row:");
  com0_write(itoa(cterm_cursor_row,debug_buffer,10));
  com0_write(" offset:");
  com0_write(itoa(buff_offset,debug_buffer,10));
  com0_write("\n\r");
#endif
  if(a == '\r'){
    cterm_cursor_col = 0;
  } else if ( a == '\n' ){
    cterm_advance_line();
  } else {
    cterm_video[buff_offset] = a;
    cterm_video[buff_offset+1] = cterm_current_vga_color;
    cterm_advance_cursor();
  }
#ifdef DEBUG
  com0_write("D> ---^^^--- cterm_write_char ---^^^---\n\r");
#endif
}

void cterm_write( char* str ){
  for(unsigned int i = 0; str[i] != '\0'; i++){
    cterm_write_char(str[i]);
  }
}

void cterm_put_char( char a, uint8_t row, uint8_t col ){
  uint8_t cursor_row = cterm_cursor_row;
  uint8_t cursor_col = cterm_cursor_col;
  cterm_set_cursor_pos( row, col );
  cterm_write_char( a );
  cterm_set_cursor_pos( cursor_row, cursor_col );
}

void cterm_blit( char* str, enum vga_color* fg, enum vga_color* bg ){
  for(unsigned int i = 0; str[i] != '\0'; i++){
    cterm_set_text_color(fg[i]);
    cterm_set_background_color(bg[i]);
    cterm_write_char(str[i]);
  }
}

void cterm_blit_vga( char* str, uint8_t* colors ){
  for(unsigned int i = 0; str[i] != '\0'; i++){
    cterm_current_vga_color = colors[i];
    cterm_write_char(str[i]);
  }
}

void cterm_clear(){
#ifdef DEBUG
  com0_write("D> ---VVV--- cterm_clear ---VVV---\n\r");
#endif
  uint8_t cursor_row = cterm_cursor_row;
  uint8_t cursor_col = cterm_cursor_col;
  cterm_set_cursor_pos(0, 0);
  for(int i = 0; i < cterm_rows * cterm_cols; i++){
#ifdef DEBUG
    com0_write("D> cterm_cursor_row=");
    com0_write(itoa(cterm_cursor_row,debug_buffer,10));
    com0_write("; cterm_cursor_col=");
    com0_write(itoa(cterm_cursor_col,debug_buffer,10));
    com0_write("\n\r");
#endif
    cterm_write_char(' ');
  }
  cterm_set_cursor_pos(cursor_row, cursor_col);
#ifdef DEBUG
  com0_write("D> ---^^^--- cterm_clear --^^^---\n\r");
#endif
}

void cterm_clear_row( uint8_t row){
  uint8_t cursor_row = cterm_cursor_row;
  uint8_t cursor_col = cterm_cursor_col;
  cterm_set_cursor_pos( row, 0 );
  for(int i = 0; i < cterm_cols; i++){
    cterm_write_char(' ');
  }
  cterm_set_cursor_pos( cursor_row, cursor_col );
}

void cterm_clear_cursor_row(){
  cterm_clear_row(cterm_cursor_row);
}

void cterm_clear_col( uint8_t col){
  for(uint8_t i = 0; i < cterm_cols; i++){
    cterm_set_cursor_pos(i, col);
    cterm_write_char(' ');
  }
}

void cterm_clear_cursor_col(){
  cterm_clear_col(cterm_cursor_col);
}

void cterm_get_cursor_pos( uint8_t* row, uint8_t* col ){
  *row = cterm_cursor_row;
  *col = cterm_cursor_col;
}

void cterm_set_cursor_pos( uint8_t row, uint8_t col ){
  //TODO sanity checks
  cterm_cursor_row = row;
  cterm_cursor_col = col;
}

//void cterm_set_cursor_blink( bool blink ){}

void cterm_get_size( uint8_t* rows, uint8_t* cols ){
  *rows = cterm_rows;
  *cols = cterm_cols;
}

//void cterm_scroll( uint8_t n );

void cterm_set_text_color( enum vga_color c ){
  uint8_t color = cterm_build_color( c, cterm_get_background_color() );
  cterm_set_vga_color( color );
}

void cterm_set_background_color( enum vga_color c ){
  uint8_t color = cterm_build_color( cterm_get_text_color(), c );
  cterm_set_vga_color( color );
}

void cterm_set_vga_color( uint8_t color ){
  cterm_current_vga_color = color;
}

/* cterm_set_current_page( uint8_t page ), */
/* cterm_move_pages( uint8_t source_page, uint8 destination_page ), */
/* cterm_copy_page_to_a( uint8_t source_page, char* destination_a, int a_len ), */
/* cterm_copy_a_to_page( char* source_a, int a_len, uint8_t destination_page ); */

uint8_t cterm_build_color( enum vga_color fg, enum vga_color bg ){
  return fg | bg << 4;
}

//uint8_t cterm_get_current_page(){}

//uint8_t cterm_get_page_count(){}

uint16_t cterm_get_buffer_offset(){
  return (cterm_cursor_col * 2)+(cterm_cursor_row * (cterm_cols * 2));
}

enum vga_color cterm_get_text_color(){
  return cterm_current_vga_color & 0x0F;
}

enum vga_color cterm_get_background_color(){
  return (cterm_current_vga_color & 0xF0) >> 4;
}
