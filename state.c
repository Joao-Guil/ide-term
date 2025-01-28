#include <ncurses.h>
#include "state.h"
#include "buffer.h"

void handle_input(bState *bs, int input) {
  // mode independant

  switch (input) {
    case KEY_UP:
      tb_up(&bs->buffer);
      return;
    case KEY_DOWN:
      tb_down(&bs->buffer);
      return;
    case KEY_LEFT:
      tb_left(&bs->buffer);
      return;
    case KEY_RIGHT:
      tb_right(&bs->buffer);
      return;
    default:
      break;
  }

  // insert mode
  if (bs->mode == 1) {
    switch (input) {
    case '\n':
    case 13:
    case KEY_ENTER:
      tb_appendnewline(&bs->buffer);
      break;
    case KEY_BACKSPACE:
      tb_remove(&bs->buffer);
      break;
    case 27:
      bs->mode = 0;
      break;
    default:
      tb_insert(&bs->buffer, input);
      break;
    }
  }
  // normal mode
  else if (bs->mode == 0) {
    switch (input) {
    case 'Q':
      // TODO: fancier way to exit because we have style.
      bs->should_exit = 1;
      break;
    case 'S':
      tb_save(bs->buffer, bs->filename);
      break;
    case 'i':
      bs->mode = 1;
      break;
    }
  }
}