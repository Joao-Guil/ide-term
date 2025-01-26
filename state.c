#include "state.h"

void handle_input(bState *bs, int input) {
  // insert mode
  if (bs->mode == 1) {
    switch (input) {
    case '\n':
    case 13:
    // enter or return idk
    case KEY_ENTER:
      tb_initline(&bs->buffer);
      break;
    case KEY_BACKSPACE:
      tb_remove(&bs->buffer);
      break;
    default:
      tb_insert(&bs->buffer, input);
      break;
    }
  }
  // normal mode
  else {
    switch (input) {
    case 'Q':
      // TODO: fancier way to exit because we have style.
      for (int i = 0; i < bs->buffer.size; i++) {
        free(bs->buffer.data[i]);
      }
      free(bs->buffer.data);
      endwin();
      break;
    case 'S':
      tb_save(bs->buffer, bs->filename);
      break;
    }
  }
}