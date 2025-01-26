#ifndef BUFFER_H
#define BUFFER_H
typedef struct {
  char **data;
  // buffer cursor position
  int cx;
  int cy;
  int size;
} TextBuffer;

void tb_initline(TextBuffer *b);
void tb_insert(TextBuffer *b, char ch);
void tb_remove(TextBuffer *b);
// instead of receiving struct bState that will cause recusive include,
// we accept the filename and the buffer
void tb_save(TextBuffer b, char *filename);
#endif