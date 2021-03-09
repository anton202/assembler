#include<stdio.h>
#include "utility.h"

void main(void){
  char *p;
  int i;
   p = convertNumberToBinary(-1264);
   for ( i = 0; i < 12; i++)
   {
        printf("%d",p[i]);
   }
   putchar('\n');
   
}