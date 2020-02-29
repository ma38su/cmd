#include <stdio.h>
#include <stdlib.h>

static void die(const char *s);
static void do_cat(const char *path);

int main(int argc, char *argv[])
{
  if (argc == 1) {
    do_cat(NULL);
  }
  int i;
  for (i = 1; i < argc; ++i) {
    do_cat(argv[i]);
  }
  return 0;
}

static void do_cat(const char *path) {
  FILE *f;
  int c;

  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
    path = "stdin";
  }
  if (!f) die(path);
  while ((c = fgetc(f)) != EOF) {
    if (putchar(c) < 0) die(path);
  }
  fclose(f);
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}
