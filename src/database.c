#include <stdio.h>
#include <stdlib.h>
/*simple list with sentinel element to simplified a litle pusk and pop*/
struct list{
    int* feat;
    size_t len;
    struct list* next;
    char* name;
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
struct list* list_find(struct list *l)
{
   return NULL /* TODO: how to find a people */
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
struct list* build_elm(char* name,int* feat, size_t len)
{
  struct list *tmp = malloc(sizeof(list));
  if (tmp) {
    tmp->next = NULL;
    tmp->len = len;
    tmp->name = name;
    tmp->feat = feat;
  }
  else {
    printf("ERROR : malloc problem");
  }
  return tmp
}
