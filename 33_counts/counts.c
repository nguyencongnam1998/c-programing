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
    ans->cntArr=NULL;
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
      if(!strcmp(c->cntArr[i]->string,str))
      {
	c->cntArr[i]->count++;
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
    c->cntArr=realloc(c->cntArr,(c->Arr_size+1)*sizeof(*c->cntArr));
    c->Arr_size++;
    c->cntArr[c->Arr_size-1]=cnt;
  }
  else
  {
    free(str);
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for(int i=0; i < c->nCounts; i++) {
    if(c->counts[i]->name == NULL) {
      unknownIndex = i;
    } else {
      fprintf(outFile, "%s: %d\n", c->counts[i]->name, c->counts[i]->count);
    }
  }
  if (unknownIndex != -1) {
    fprintf(outFile, "<unknown> : %d\n", c->counts[unknownIndex]->count);
  }
}
void freeCounts(counts_t * c) {
  //WRITE ME
  for(size_t i=0;i<c->Arr_size;i++)
  {
    free(c->cntArr[i]->string);
    free(c->cntArr[i]);
  }
  free(c->cntArr);
  free(c);
}
