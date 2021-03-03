#include <stdio.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"

int main(int argc, char *argv[]){
    char line[80];
    FILE *fp;
    int lineReadStatus;
    char *symbol;
    int lineIndex = 0;

    if (argc == 1)
    {
        printf("\nError: Please enter file name\n");
        return 0;
    }

    if(checkFiles(argc,argv) == -1)
    {
        return 0;
    }
    
    fp = fopen(addExtentitonToFileName(argv[1]),"r");
    lineReadStatus = readLine(line,fp,1);

    if(lineReadStatus != 1)
    {
        
        symbol = isSymbol(line,&lineIndex);
        if(symbol != NULL)
        {
            printf("the symbol is: %s \n",symbol);
            
        }
        printf("line index: %d\n",lineIndex);
    }

    return 1;
}