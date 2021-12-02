#include <stdio.h>

int main(){
    FILE *fin = fopen("inputs","r");
    int absX=0;
    int absY=0;
    char dir[20];
    int i;
    while (fscanf(fin,"%s %d",dir,&i) == 2){
      switch(dir[0]){
        case 'f': absX+=i; break;
        case 'd': absY+=i; break;
        case 'u': absY-=i; break;
      }
    }
    printf("%d\n",absY*absX);


    return 0;
}
