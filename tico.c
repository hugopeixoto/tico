#include <stdio.h>
#include <string.h>

int utflength(char c) {
  int i;
  for (i = 0; (c>>7)&1; ++i) {
    c <<= 1;
  }
  return i?i:1;
}

void shorten(const char* path) {
  const char* p = NULL;

  while (*path == '/') {
    fputc('/', stdout);
    ++path;
  }

  while ((p = strchr(path, '/'))) {
    int bytes = utflength(*path);

    printf("%.*s/", bytes, path);

    path = p + 1;
  }

  puts(path);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <path>\n", argv[0]);
    return 1;
  }

  shorten(argv[1]);
  return 0;
}
