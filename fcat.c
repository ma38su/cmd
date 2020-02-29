#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048
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
  unsigned char buf[BUFFER_SIZE];
  int n;

  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
    path = "stdin";
  }
  if (!f) die(path);
  for (;;) {
    n = fread(buf, sizeof(char), BUFFER_SIZE, f);
    if (n < 0) die(path);
    if (n == 0) break;
    if (fwrite(buf, sizeof(char), n, stdout) < 0) die(path);
  }
  fclose(f);
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}
