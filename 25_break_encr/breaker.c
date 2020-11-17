#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getintoArray(int *Arr, FILE * f){
  int c;
  while((c=fgetc(f)) != EOF)
  {
    if(isalpha(c))
    {
      c = tolower(c);
      c = c - 'a';
      Arr[c] = Arr[c]+1;
    }
  }
}

int maxId(int * Arr)
{
  int maxx = Arr[0];
  int maxIdx = 0;
  for(int i=0; i<26; i++)
  {
    if(Arr[i]>maxx)
    {
      maxx = Arr[i];
      maxIdx = i;
    }
  }
  return maxIdx;
}

int main(int argc, char ** argv){
  if(argc!=2){
    fprintf(stderr, "Usage: need more argument\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1],"r");
  if(f==NULL){
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int MyArr[26] = {0};
  getintoArray(MyArr, f);
  int max = maxId(MyArr);
  int key = (max + 'a' - 'e' + 26)%26;
  printf("%d\n", key);
}
