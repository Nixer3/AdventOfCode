#include <stdio.h>
#include <string.h>

#define QSIZE 3
void qpush(int *q, int a){
  for(int i = QSIZE-1; i>=1 ; i--)
    q[i] = q[i-1];
  q[0] = a;
}
int qsum(int *q){
  int out = 0;
  for(int i=0;i<QSIZE;i++)
    out+=q[i];
  return out;
}
int main(void) {
  int incs=0;
  FILE *f = fopen("inputs","r");
  int depth = -1, lastd = -1;
  int queue[QSIZE];
  memset(queue,0,QSIZE*sizeof(int));
  int cnt =0;
  while(fscanf(f, "%d",&depth)!= EOF){
    cnt++;
    qpush(queue, depth);
    depth = qsum(queue);
    if(depth > lastd && cnt > 3){
      incs++;
    }
    lastd = depth;
  }
  printf("increased: %4d times", incs);
  fclose(f);
  return 0;
}