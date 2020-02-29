#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_NLINES 10

static void die(const char *s);
static void do_head(const char *path, long nlines);
static void err(const char *prog);

int main(int argc, char *argv[])
{
  int opt;
  long nlines = DEFAULT_NLINES;
  while ((opt = getopt(argc, argv, "n:")) != -1) {
    switch (opt) {
      case 'n':
        nlines = atol(optarg);
        break;
      case '?':
        err(argv[0]);
        break;
    }
  }
  if (optind == argc) {
    do_head(NULL, nlines);
  } else {
    int i;
    for (i = optind; i < argc; ++i) {
      do_head(argv[i], nlines);
    }
  }
  return 0;
}

static void err(const char *prog) {
  fprintf(stderr, "Usage: %s n\n", prog);
  exit(1);
}
static void do_head(const char *path, long nlines)
{
  int c;
  char ch;
  FILE *f;
  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
  }
  if (!f) die(path);
  while ((c = fgetc(f)) != EOF) {
    ch = (char) c;
    if (putchar(c) < 0) die(path);
    if (c == '\n' && --nlines == 0) {
      break;
    }
  }
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}
