
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
/*simple list with sentinel element to simplified a litle pusk and pop
  pay attention you on the previous element use ->next to work on your element*/

struct list{
    int* feat;
    size_t len;
    struct list* next;
    char* name;
  char* path;
};

struct list* list_empty(void)
{
  struct list* tmp = malloc(sizeof(struct list));
  if(tmp){
    tmp->feat = NULL;
    tmp->next = NULL;
    tmp->len =0;
    tmp->name = NULL;
  }
  return tmp;
}
size_t list_len(struct list *l){
  size_t len;
  for(len=0; l; l = l->next)
    len++;
  return len-1;
}
void list_push_front(struct list *l, struct list *elm){
  elm->next = l->next;
  l->next = elm;
}


struct list* find_name(struct list *l,char* name)
{
  while(l->next && (strcmp(name,l->next->name)!=0))
    {
      l= l->next;
    }
  if(l->next)
    {
      return l;
    }
  return NULL;
  
}

struct list* list_pop_front(struct list *l)
{
  if(l->next){
    struct list * tmp = l->next;
    l->next = l->next->next;
    return tmp;
  }
  return NULL;

}
 struct list* build_elm(char* name,int* feat, size_t len,char* path)
{
  struct list *tmp = malloc(sizeof(struct list));
  if (tmp) {
    tmp->next = NULL;
    tmp->len = len;
    tmp->name = name;
    tmp->feat = feat;
    tmp->path = path;
  }
  else {
    printf("ERROR : malloc problem");
  }
  return tmp;
}

void save(struct list *l,char* path)
{
  FILE* cur= NULL;
  l=l->next;
  for(;l;l = l->next)
    {
      path = realloc(path,(strlen(path)+strlen(l->name))*sizeof(char));
      path=strcat(path,l->name);
      cur = fopen(path,"w+");
      if(cur)
	{
	  fprintf(cur,"%zu\n",l->len);
	  fprintf(cur,"%s\n",l->path);
	  for(size_t i =0;i<l->len;i++)
	    fprintf(cur,"%d\n",*((l->feat)+i));
	  fclose(cur);  
	}
    }
}


struct list* load(char* path)
{
  DIR *dir = NULL;
  struct dirent*cur =NULL;
  dir=opendir(path);
  struct list* l =list_empty();
  
  if(dir == NULL)
    {
      perror("");
      return NULL;
    }
 
  while ((cur = readdir(dir)) != NULL)
    if(cur->d_name[0]!= '.')
      {
	struct list* tmp = malloc(sizeof(struct list));
	tmp->name = cur->d_name;
	FILE* tmp1 = fopen(cur->d_name,"r");
	fscanf(tmp1,"%zu/n",(&(tmp->len)));
      }
   
  return l; 
}

int main()
{
  load("../");
}
