#include <stdio.h>
#include "utility.h"

int main(void)
{

     int number;

     number = isImmedtiateOperand("#+55.55", 1);
     printf("\nthe number is %d\n",number);
     return 1;
}