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
    int isDataDirective;
    int c, number;

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
            isSymbolValid(symbol,1);
            
        }
        printf("\nline index: %d\n",lineIndex);

        isDataDirective = checkIfDataDirective(line, &lineIndex);
        if(!isDataDirective)
        {
            if(!checkIfSemicolon(line,&lineIndex))
            {
                while((c = checkDataFormat(line,&lineIndex,&number,1)) != 0)
                {
                    if(!checkIfSemicolon(line,&lineIndex))
                    {
                        printf("Error: number parameters should be seperated by ','");
                        return 0;
                    }
                    printf("\n%d\n",number);
                }
                 printf("\n%d\n",number);
            }
        }

        printf("\nline index: %d\n",lineIndex);
    }

    return 1;
}