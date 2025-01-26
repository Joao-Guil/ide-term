#include <ncurses.h>
#include "buffer.c"
#include "state.c"

void myscr() {
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
  int input = -1;

  myscr();

  while (input != 'q') {
    input = getch();
    
    handle_input(&bs, input);

    refresh();
    clear();
    display(&buffer);
  }

  for (int i = 0; i < (int) buffer.size; i++) {
    free(buffer.data[i]);
  } free(buffer.data);

  endwin();
  return 0;
}