#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

char ** read_F(FILE *f, char **Arr, size_t *index){
  char *line=NULL;
  size_t sz=0;
  while(getline(&line,&sz,f)>=0){
    Arr=realloc(Arr,((*index)+1)*sizeof(*Arr));
    Arr[*index]=malloc((strlen(line)+1)*sizeof(Arr[*index]));
    strcpy(Arr[*index],line);
    free(line);
    line=NULL;
    (*index)++;
  }
  free(line);
  return Arr;
}

void Print_and_Free(char **Arr, size_t index){
  size_t i=0;
  while(i<index){
    fprintf(stdout,"%s",Arr[i]);
    free(Arr[i]);
    i++;
  }
  free(Arr);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  size_t index=0;
  char **array=NULL;
  if(argc==1){
    array=read_F(stdin,array,&index);
    sortData(array,index);
    Print_and_Free(array,index);
    array=NULL;
  }
  else{
    for(size_t i=1;i<argc;i++){
      FILE *input=fopen(argv[i],"r");
      if(input==NULL){
	fprintf(stderr,"Can not open file '%s'\n",argv[i]);
	return EXIT_FAILURE;
      }
      index=0;
      array=read_F(input,array,&index);
      sortData(array,index);
      Print_and_Free(array,index);
      array=NULL;
      if(fclose(input)!=0){
	fprintf(stderr,"Can not close file '%s'\n",argv[i]);
	return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
