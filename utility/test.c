#include <stdio.h>
#include "utility.h"

int main(void)
{

     int number;
     

     number = getOperandsAddressingMode("%dj^^dn", 1);
     printf("\nthe number is %d\n", number);
     return 1;
}