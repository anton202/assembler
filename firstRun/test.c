#include <stdio.h>
#include <ctype.h>
#include "firstRun.h"
#include "../hellper/hellper.h"
#include "../utility/utility.h"
#include "../machineCode/machineCode.h"

int main(int argc, char *argv[])
{
    char line[80];
    FILE *fp;
    int lineReadStatus;
    char *symbol;
    int lineIndex = 0;
    int isDataDirective;
    int  number, getNumberStatus;
    Data *savedData;

    if (argc == 1)
    {
        printf("\nError: Please enter file name\n");
        return 0;
    }

    if (checkFiles(argc, argv) == -1)
    {
        return 0;
    }

    fp = fopen(addExtentitonToFileName(argv[1]), "r");
    lineReadStatus = readLine(line, fp, 1);

    if (lineReadStatus != 1)
    {

        symbol = isSymbol(line, &lineIndex);
        if (symbol != NULL)
        {
            printf("the symbol is: %s \n", symbol);
            isSymbolValid(symbol, 1);
        }
        printf("\nline index: %d\n", lineIndex);

        isDataDirective = checkIfDataDirective(line, &lineIndex);
        if (!isDataDirective)
        {
            /*check if there is at least on space betwen .data and a number*/
            if(*(line + lineIndex) != ' ')
            {
                printf("line number %d Erorr: there must be at least one space between .data and the data itself",1);
                return 0;
            }

            /*skip all the white space between .data and the first argument*/
            while (isspace(*(line + lineIndex))){
                lineIndex++;
            }
           
            do{
                getNumberStatus = getNumber(line,&number,&lineIndex);
                if(getNumberStatus > -1)
                {
                    /*hnadle error*/
                    printf("\nline number:%d Erorr: %c is not a valid number\n",1,getNumberStatus);
                    return 0;
                }
                if(number > -2047 && number < 2047)
                {
                   savedData = addData(number);
                   printf("\nnumber read: %d",number);
                }else{
                    printf("\nnumber line %d Error: number %d is to big\n",1,number);
                    return 0;
                }
                
            } while(checkIfSemicolon(line, &lineIndex,1) != -1);
            
        }
        
    }

    return 1;
}