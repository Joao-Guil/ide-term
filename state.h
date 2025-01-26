#ifndef STATE_H
#define STATE_H
#include "buffer.h"

typedef struct {
  TextBuffer buffer;
  int mode;
  char *filename;
} bState;

void handle_input(bState *bs, int input);
#endif