#include "database.h"
/*simple list with sentinel element to simplified a litle pusk and pop
  pay attention you on the previous element use ->next to work on your element*/


struct list* list_empty(void)
{
  
  struct list* b = malloc(sizeof(struct list));
  if(b){
    b->feat = NULL;
    b->next = NULL;
    b->len =0;
    b->name = NULL;
  }
  return b;
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

void save(struct list *l)
{
  FILE* cur= NULL;
  l=l->next;
  char buf[256]="";
  while(l)
    {
      
      //path = realloc(path,(strlen(path)+strlen(l->name))*sizeof(char));
      //path=strcat(path,l->name);
      strcpy(buf,"data/");
      strcat(buf,l->name);
      cur = fopen(buf,"w+");
      if(cur)
	{
	  fprintf(cur,"%zu\n",l->len);
	  fprintf(cur,"%s\n",l->path);
	  for(size_t i =0;i<l->len;i++)
	    fprintf(cur,"%d\n",*((l->feat)+i));
	  fclose(cur);  
	}
      l=l->next;
    }
}


struct list* load()
{
  DIR *dir = NULL;
  struct dirent*cur =NULL;
  dir=opendir("data");
  struct list* l =list_empty();
  
  if(dir == NULL)
    {
      mkdir("data",0700);
      return l;
    }
  char buff[128],str[32];
  while ((cur = readdir(dir)) != NULL)
    if(cur->d_name[0]!= '.')
      {
	struct list* tmp = malloc(sizeof(struct list));
	tmp->name = cur->d_name;
	strcpy(buff,"data/");
	strcat(buff,cur->d_name);
	FILE* tmp1 = fopen(buff,"r");
	if (!tmp1)
	  return NULL;
	fgets(str,32,tmp1);
	tmp->len = atoi(str);
	tmp->path= malloc(64*sizeof(char));
	fscanf(tmp1,"%s\n",tmp->path);
	tmp->feat= malloc(tmp->len*sizeof(int));
	for(size_t i =0; i<tmp->len;i++)
	  {
	    fscanf(tmp1,"%d\n",((tmp->feat)+i));
	  }
	tmp->next= NULL;
	list_push_front(l,tmp);
	  
      }
   
  return l; 
}

int add(struct list* l ,char* name,char * path)
{
  if(find_name(l,name))
    return 1;
  else
    {
      list_push_front(l,build_elm(name,NULL,0,path));
      return 0;
    }
}

int del(struct list *l,char*name)
{
  struct list *tmp=  list_pop_front(find_name(l,name));
  char buff[32];
  strcpy(buff,"data/");
  strcat(buff,name);
  remove(buff);
  if(tmp)
    free(tmp);
  return 0;
}



int main()
{
  //struct list* l = list_empty();
  //int myArray[10] = {1,2,3,4,5};
  // struct list* tmp = build_elm("name1",myArray,5,"dd/dd/dd");
  // struct list* tmp1 = build_elm("name2",myArray,5,"dd/dd/dd");
  //struct list* tmp2 = build_elm("name3",myArray,5,"dd/dd/dd");
  //add(l,"dq","f/g/h");
  //add(l,"ds","s/d/f");
  //add(l,"dd","g/h/j");  
  //char path[100] =""; 
  //save(l);
  struct list*d= load();
  //printf("%s\n",l->next->name);
  /*while(d->next){
    printf("%s : %s\n",d->next->name, d->next->path);
    d = d->next;
    }*/
  del(d,"dd");
    //printf("%s\n",find_name(l,"name1")->next->name);
  return 0;
}

