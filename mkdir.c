#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static char *lstrchr(const char *path);
static void die(const char *s);
static int do_mkdir(const char *path, const bool opt_p);
static char *parent_path(const char *path);

static void err(const char *prog);

int main(int argc, char *argv[])
{
  int i;
  int opt;
  bool opt_p = true;
  while ((opt = getopt(argc, argv, "p")) != -1) {
    switch (opt) {
      case 'p':
        opt_p = 1;
        break;
      case '?':
        err(argv[0]);
        break;
    }
  }
  if (argc == optind) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
    return 1;
  }

  for (i = optind; i < argc; ++i) {
    char *path = argv[1];
    if (do_mkdir(path, opt_p) < 0) {
      die(path);
    }
  }
  return 0;
}

static void err(const char *prog)
{
  fprintf(stderr, "Usage: %s n\n", prog);
  exit(1);
}

static int do_mkdir(const char *path, const bool opt_p)
{
  if (mkdir(path, 0777) < 0) {
    if (!opt_p) return -1;
    char* parent = parent_path(path);
    if (do_mkdir(parent, opt_p) < 0) {
      return -1;
    }
    return mkdir(path, 0777);
  }
  return 0;
}

static char* parent_path(const char *path) {
  char *p, *parent;
  int n;

  p = strrchr(path, '/');
  n = (int) (p - path);
  parent = calloc(n + 1, sizeof(char));
  strncpy(parent, path, n);
  parent[n] = '\0';

  return parent;
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
