#include <stdio.h>

int main(){
    FILE *fin = fopen("slova.txt","r");
    int absX=0;
    int absY=0;
    int aim=0;
    char dir[20];
    int i;
    while (fscanf(fin,"%s %d",dir,&i) == 2){
      switch(dir[0]){
        case 'f': aim+=absY*i; break;
        case 'd': absY+=i; break;
        case 'u': absY-=i; break;
      }
    }
    printf("%d\n",aim*absX);


    return 0;
}
