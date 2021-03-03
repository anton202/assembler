#include <stdio.h>
#include "machineInstructions.h"

void main(void){
int i;
char *insCode = NULL;

insCode = searchOpperation("aded");

if(insCode != NULL){
for(i = 0; i < 8; i++){
printf("%d",*(insCode + i));
}
}

return;
}

