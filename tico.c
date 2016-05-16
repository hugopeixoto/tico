#include <stdio.h>
#include <string.h>

int utflength(char c) {
  int i;
  for (i = 0; (c>>7)&1; ++i) {
    c <<= 1;
  }
  return i?i:1;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s <path>\n", argv[0]);
    return 1;
  }

  while (argv[1][0] == '/') {
    fputc('/', stdout);
    ++argv[1];
  }

  const char* p = argv[1];
  const char* q = NULL;
  while ((q = strchr(p, '/'))) {
    int bytes = utflength(*p);

    printf("%.*s/", bytes, p);

    p = q + 1;
  }

  puts(p);
  return 0;
}
