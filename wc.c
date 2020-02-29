#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void die(const char *s);
static int do_wcl(const char *path);
static void err(const char *prog);

int main(int argc, char *argv[])
{
  int opt;
  int lopt = 0;
  while ((opt = getopt(argc, argv, "l")) != -1) {
    switch (opt) {
      case 'l':
        lopt = 1;
        break;
      case '?':
        err(argv[0]);
        break;
    }
  }
  if (lopt) {
    int i;
    int l;
    if (argc == optind) {
      printf("%7d\n", do_wcl(NULL));
    } else {
      for (i = optind; i < argc; ++i) {
        printf("%7d %s\n", do_wcl(argv[i]), argv[i]);
      }
    }
  } else {
    err(argv[0]);
  }

  return 0;
}

static void err(const char *prog) {
  printf("Usage: %s -n n file\n", prog);
  exit(1);
}

static int do_wcl(const char *path) {
  FILE *f;
  int l = 0;
  int c;
  if (path) {
    f = fopen(path, "r");
  } else {
    f = stdin;
    path = "";
  }
  if (!f) die(path);
  while ((c = fgetc(f)) != EOF) {
    char ch = (char) c;
    if (ch == '\n') l++;
  }
  fclose(f);
  return l;
}

static void die(const char *s)
{
  perror(s);
  exit(1);
}

