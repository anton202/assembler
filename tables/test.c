#include <stdio.h>
#include "tables.h"

int main(void){

int i;

i = isValidAddressingMode("lea",2,1);
printf("is addressing mode valid: %d",i);
return 1;
}

