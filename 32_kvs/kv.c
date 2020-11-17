#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t* split(char* str){

  char* val1=strchr(str,'=');
  *val1='\0';
  val1 ++;
  char* n=strchr(val1,'\n');
  if(n != NULL) *n='\0';

  kvpair_t* Pair = malloc((size_t) sizeof(*Pair));
  Pair ->key=str;
  Pair ->value=val1;
  return Pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open the file");
    return NULL;
  }

  //READ
  char* line= NULL;
  size_t sz=0;
  kvpair_t* curr_pair = NULL;

  kvarray_t* Arr= malloc((size_t)(sizeof(*Arr)));
  Arr->size = 0;
  Arr->arr=NULL;

  while (getline(&line,&sz, f) >= 0)
  {
    curr_pair = split(line);
    Arr->arr = realloc(Arr->arr,(Arr->size+1) * sizeof(*Arr->arr));
    Arr->arr[Arr->size] = curr_pair;
    Arr->size ++;
    line = NULL;
  }
  free(line);
  int result=fclose(f);
  if (result !=0)
  {
    return NULL;
  }
  return Arr;
}

void freeKVs(kvarray_t * pairs) {

  //WRITE ME
  for(int i=0 ;i<pairs->size;i++)
  {
    free(pairs->arr[i]->key);
    free(pairs->arr[i]);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t* curr_pair;
  for(int i=0;i<pairs->size;i++)
  {
    curr_pair=pairs->arr[i];
    printf("key = '%s' value = '%s'\n" ,curr_pair->key, curr_pair->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t* curr_pair;
  for(int i=0;i<pairs->size;i++)
  {
    curr_pair=pairs->arr[i];
    if (! strcmp(curr_pair->key,key))
    {
      return  curr_pair->value;
    }
  }
  return NULL;
}
