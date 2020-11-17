#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t *ans=malloc(sizeof(*ans));
  if(ans!=NULL)
  {
    ans->AcntArr=NULL;
    ans->Arr_size=0;
  }
  return ans;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  char *str=NULL;
  if(name==NULL)
  {
    str=strdup("Unknown");
  }
  else
  {
    str=strdup(name);
  }

  int str_is_found=0;
  if(c->Arr_size>0)
  {
    for(size_t i=0;i<c->Arr_size;i++)
    {
      if(!strcmp(c->AcntArr[i]->string,str))
      {
	c->AcntArr[i]->count++;
	str_is_found=1;
      }
    }
  }

  if(!str_is_found)
  {
    one_count_t *cnt=malloc(sizeof(*cnt));
    assert(cnt!=NULL);
    cnt->string=str;
    cnt->count=1;
    c->AcntArr=realloc(c->AcntArr,(c->Arr_size+1)*sizeof(*c->AcntArr));
    c->Arr_size++;
    c->AcntArr[c->Arr_size-1]=cnt;
  }
  else
  {
    free(str);
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  size_t unknown_index=c->Arr_size;
  for(size_t i=0;i<c->Arr_size;i++)
  {
    if(!strcmp(c->AcntArr[i]->string,"unknown"))
    {
      unknown_index=i;
      continue;
    }
    fprintf(outFile,"%s: %ld\n",c->AcntArr[i]->string,c->AcntArr[i]->count);
  }
  if(unknown_index<c->Arr_size && c->AcntArr[unknown_index]->count>0)
  {
    fprintf(outFile,"<%s> : %ld\n",c->AcntArr[unknown_index]->string,c->AcntArr[unknown_index]->count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0;i<c->Arr_size;i++)
  {
    free(c->AcntArr[i]->string);
    free(c->AcntArr[i]);
  }
  free(c->AcntArr);
  free(c);
}
