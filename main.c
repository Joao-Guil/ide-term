#include <ncurses.h>
#include "buffer.c"
#include "state.c"

void tinit() {
  initscr();
  noecho();
  raw();
  keypad(stdscr, TRUE);
  cbreak();
}

int main(int argc, char const *argv[]) {
  TextBuffer buffer = {0};
  bState bs = {0};

  bs.buffer = buffer;
  bs.mode = 1;
  bs.filename = argc >= 2 ? (char *) argv[1] : "untitled.txt";
  int input = -1;

  tinit();

  while (bs.should_exit == 0) {
    input = getch();
    
    handle_input(&bs, input);

    refresh();
    clear();
    display(&bs.buffer);
  }

  for (int i = 0; i < (int) buffer.size; i++) {
    free(buffer.data[i]);
  } free(buffer.data);

  endwin();
  return 0;
}