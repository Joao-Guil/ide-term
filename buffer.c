#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "buffer.h"

void tb_initline(TextBuffer *b) {
  b->data = realloc(b->data, sizeof(char *) * (b->size + 1));
  b->data[b->size] = malloc(1);
  b->data[b->size][0] = '\0';
  b->size++;
}

void tb_appendnewline(TextBuffer *b) {
  tb_initline(b);
  b->cy++;
  b->cx = 0;
}

void tb_insert(TextBuffer *b, char ch) {
  if (b->size <= b->cy) {
    tb_initline(b);
  }
  size_t len = strlen(b->data[b->cy]);
  b->data[b->cy] = realloc(b->data[b->cy], len + 2);
  memmove(&b->data[b->cy][b->cx + 1], &b->data[b->cy][b->cx], len - b->cx + 1);
  b->data[b->cy][b->cx] = ch;
  b->cx++;
}

void tb_remove(TextBuffer *b) {
  // todo: remove line
  if (b->size >= 1 && strlen(b->data[b->cy]) > 0) {
    size_t len = strlen(b->data[b->cy]);
    memmove(&b->data[b->cy][b->cx - 1], &b->data[b->cy][b->cx], len - b->cx + 1);
    b->cx -= 1;
  } else {
    // if unhandled cases or illegal cases.
    return;
  }
}

void tb_up(TextBuffer *b) {
  if (b->cy > 0) {
    b->cy -= 1;
    b->cx = (int) strlen(b->data[b->cy]) >= b->cx ? b->cx : (int) strlen(b->data[b->cy]);
  }
}

void tb_down(TextBuffer *b) {
  if (b->cy + 1 <= b->size) {
    b->cy += 1;
    b->cx = (int) strlen(b->data[b->cy]) >= b->cx ? b->cx : (int) strlen(b->data[b->cy]);
  }
}

void tb_right(TextBuffer *b) {
  if (b->cx < (int) strlen(b->data[b->cy])) {
    b->cx += 1;
  }
}

void tb_left(TextBuffer *b) {
  if (b->cx > 0) {
    b->cx -= 1;
  }
}

void tb_save(TextBuffer b, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f == NULL) {
    return;
  }
  for (int i = 0; i < b.size; i++) {
    if (strcmp(b.data[i], "") == 0) {
      fprintf(f, "\n");
    } else {
      fprintf(f, "%s\n", b.data[i]);
    }
  }
  fclose(f);
}

void display(TextBuffer *b) {
  for (int i = 0; i < b->size; i++) {
    wprintw(stdscr, "%s\n", b->data[i]);
  }
  move(b->cy, b->cx);
}