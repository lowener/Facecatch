# ifndef DATABASE_H_
# define DATABASE_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

struct list{
  int* feat;
  size_t len;
  struct list* next;
  char* name;
  char* path;
};

size_t list_len(struct list *l);
struct list* find_name(struct list *l, char *name);
void save(struct list *l);
struct list *load();
int add(struct list *l,char* name,char*path);
int del(struct list *l,char* name);


# endif
