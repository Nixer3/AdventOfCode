#include <stdio.h>
int main(void) {
  int incs=0;
  FILE *f = fopen("inputs","r");
  int depth = -1, lastd = -1;
  while(fscanf(f, "%d",&depth)!= EOF){
    if(depth > lastd){
      incs++;
    }
    lastd = depth;
  }
  printf("increased: %d times", incs);
  fclose(f);
  return 0;
}