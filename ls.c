#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

static void do_ls(const char *path);
static void die(const char *s);


int main(int argc, char *argv[])
{
  int i;
  if (argc < 2) {
    do_ls(".");
  }
  for (i = 1; i < argc; ++i) {
    do_ls(argv[i]);
  }
  return 0;
}

static void do_ls(const char *path)
{
  DIR *d;
  struct dirent *ent;

  d = opendir(path);
  if (!d) die(path);
  while ((ent = readdir(d)) != NULL) {
    printf("%s\n", ent->d_name);
  }
  closedir(d);
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
