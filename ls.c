#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

static void do_ls(const char *path, const int rec);
static void die(const char *s);

static char *filetype(mode_t mode);


int main(int argc, char *argv[])
{
  int i;
  if (argc < 2) {
    do_ls(".", 0);
  }
  for (i = 1; i < argc; ++i) {
    do_ls(argv[i], 0);
  }
  return 0;
}

static char *filetype(mode_t mode)
{
  if (S_ISREG(mode)) return "file";
  if (S_ISDIR(mode)) return "directory";
  if (S_ISCHR(mode)) return "chardev";
  if (S_ISBLK(mode)) return "blockdev";
  if (S_ISFIFO(mode)) return "fifo";
  if (S_ISLNK(mode)) return "symlink";
  if (S_ISSOCK(mode)) return "socket";
  return "unknown";
}

static bool is_dir(const char *path) {
  struct stat st;
  if (lstat(path, &st) < 0) {
    die(path);
  }
  return S_ISDIR(st.st_mode);
}

static void do_ls(const char *path, int rec)
{
  DIR *d;
  struct dirent *ent;
  struct stat st;

  int i;
  d = opendir(path);
  if (!d) die(path);
  while ((ent = readdir(d)) != NULL) {
    if (lstat(ent->d_name, &st) < 0) {
      die(ent->d_name);
    }
    char *name = ent->d_name;
    if (strcmp(name, ".") == 0) {
      continue;
    }
    if (strcmp(name, "..") == 0) {
      continue;
    }
    for (i = 0; i < rec; ++i) {
      printf("  ");
    }
    printf("%s\n", name);
    if (is_dir(name)) {
      chdir(name);
      do_ls(".", rec + 1);
      chdir("..");
    }
  }
  closedir(d);
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
