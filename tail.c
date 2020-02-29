#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_NLINES 10

static void die(const char *s);
static long do_lc(const char *path);
static void do_tail(const char *path, long nlines);
static void err(const char *prog);

int main(int argc, char *argv[])
{
  int i;
  int opt;
  long lines;
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
  i = optind;
  if (i + 1 == argc) {
    const char *path = argv[i];
    lines = do_lc(path) - nlines;
    do_tail(path, lines);
  } else if (i < argc) {
    for (i = optind; i < argc; ++i) {
      const char *path = argv[i];
      printf("=== %s ===\n", path);
      lines = do_lc(path) - nlines;
      do_tail(path, lines);
    }
  }
  return 0;
}

static void err(const char *prog) {
  fprintf(stderr, "Usage: %s n\n", prog);
  exit(1);
}

static long do_lc(const char *path)
{
  int c;
  FILE *f;
  long l;
  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
  }
  if (!f) die(path);
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') ++l;
  }
  return l;
}

static void do_tail(const char *path, long nlines)
{
  int c;
  FILE *f;
  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
  }
  if (!f) die(path);

  while ((c = fgetc(f)) != EOF) {
    if (c == '\n' && --nlines == 0) break;
  }
  while ((c = fgetc(f)) != EOF) {
    if (putchar(c) < 0) die(path);
  }
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}

