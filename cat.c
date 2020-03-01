#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void die(const char *s);
static void do_cat(const char *path);

static void err(const char *prog);

int main(int argc, char *argv[])
{
  int i;
  int opt;
  int opt_e = 0;
  while ((opt = getopt(argc, argv, "e")) != -1) {
    switch (opt) {
      case 'e':
        opt_e = 1;
        break;
      case '?':
        err(argv[0]);
        break;
    }
  }
  if (argc == optind) {
    do_cat(NULL);
    return 0;
  }

  for (i = optind; i < argc; ++i) {
    char *path = argv[1];
    do_cat(path);
  }
  return 0;
}

static void err(const char *prog) {
  fprintf(stderr, "Usage: %s n\n", prog);
  exit(1);
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
    if (c == '\n')
      if (putchar('$') < 0) die(path);
    if (putchar(c) < 0) die(path);
  }
  fclose(f);
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}
