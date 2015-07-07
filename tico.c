#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utf.h"

typedef struct {
  size_t size;
  size_t idx;
  Rune* buffer;
} buffer_t;

void buffer_alloc(buffer_t* b, size_t n) {
  b->buffer = malloc(n * sizeof(Rune));
  b->size = n;
  b->idx = 0;
}

void buffer_dealloc(buffer_t* b) {
  free(b->buffer);

  b->buffer = NULL;
  b->idx = 0;
  b->size = 0;
}

void buffer_append(buffer_t* b, const Rune* c) {
  if (b->idx + 1 < b->size) {
    b->buffer[b->idx++] = *c;
  } else {
    b->size += BUFSIZ;
    b->buffer = realloc(b->buffer, b->size * sizeof(Rune));

    buffer_append(b, c);
  }
}

void buffer_reset(buffer_t* b) {
  b->idx = 0;
}

int shorten(FILE* in, FILE* out) {
  buffer_t buffer;
  Rune c;
  int i;

  int state = 0;

  buffer_alloc(&buffer, BUFSIZ);

  while (fgetrune(&c, in) > 0) {
    switch (state) {
      case 0:
        fputrune(&c, out);
        if (c != '/') state++;
        break;

      case 1:
        buffer_append(&buffer, &c);

        if (c == '/') {
          fputrune(&c, out);
          buffer_reset(&buffer);
          state--;
        }
        break;
    }
  }

  for (i = 0; i < buffer.idx; i++)
    fputrune(&buffer.buffer[i], out);

  buffer_dealloc(&buffer);
  return 0;
}

int main(int argc, char* argv[]) {
  return shorten(stdin, stdout);
}
